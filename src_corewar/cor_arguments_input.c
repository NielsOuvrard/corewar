/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** thr_good_corewar
*/

#include "cor_header.h"
#include "my.h"
#include "op.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

// nmb diff check

int how_many_cycles_for_next (unsigned char *mem, int index)
{
    if (mem[index] <= 0 || (mem[index] - 1) > 0x10) {
        return 0;
    }
    op_t val = op_tab[mem[index] - 1];
    // my_printf("mem de index = %d\tça return %d\n", mem[index], val.nbr_cycles);
    return val.nbr_cycles;
}

prog_t *delete_id_prog (prog_t *prog, int id)
{
    if (!id) {
        prog_t *tmp = prog;
        prog = prog->next;
        free(tmp->registres);
        free(tmp);
    }
    prog_t *expl = prog;
    while (expl && expl->next && (id-- - 1))
        expl = expl->next;
    prog_t *tmp = expl->next;
    expl->next = expl->next->next;
    free(expl->registres);
    free(expl);
    return prog;
}

void begin_virtual_machine (head_cor *cor)
{
    prog_t *expl = cor->progs;
    for (int id = 0; expl; id++) {
        my_printf("id = %d\n", id);
        if (expl->cycle_to_wait > 0) {
            expl->cycle_to_wait -= 16;
            my_printf("il rest %d cycle pour prog %d\n", expl->cycle_to_wait, expl->registres[0]);
        } else {
            my_printf("AVANT EXE COMMANDE\n");
            execute_this_commande(cor, expl);
            my_printf("APRES EXE COMMANDE\n");
            expl->cycle_to_wait = how_many_cycles_for_next(cor->mem, expl->registres[0]);
            my_printf("APRES How many cycles for next\n");
            // my_printf("cycle to wait : %d\n", expl->cycle_to_wait);
            // dump_amll(cor);
        }
        my_printf("id = %d\n", id);
        // my_printf("prog live : %d\n", expl->cycle_to_die);

        if (0 > (expl->cycle_to_die--)) {
            // my_printf("program %d decede\n", id);
            cor->progs = delete_id_prog(cor->progs, id); // il décède le con
        }
        expl = expl->next;
        // here
        // pb tourn en boucle lors d'un fork, WHY ?
    }
    // my_printf("cycle live %d\n", cor->cycle_to_die_init);
}

int my_strcmp_end (char *str1, char *str2)
{
    int size1 = my_strlen(str1), size2 = my_strlen(str2);
    for (int i1 = size1, i2 = size2; i2 > 0; i1--, i2--) {
        if (i1 <= 0)
            return str2[i2];
        if (str1[i1] != str2[i2])
            return abs(str1[i1] - str2[i2]);
    }
    return 0;
}

int how_many_champs_befor_mem (char **av)
{
    int nmb = 0;
    for (int i = 0; av[i]; i++) {
        if (!my_strcmp_end(av[i], ".cor"))
            nmb++;
    }
    return nmb;
}

head_cor *complete_with_args (int ac, char **av)
{
    head_cor *cor = create_mem();
    int start = 1;
    if (!my_strcmp(av[1], "-dump") && av[2] && my_isnbr(av[2])) {
        start += 2;
        cor->recurence_dump = my_getnbr(av[2]);
    }
    int nmb_cham = how_many_champs_befor_mem(av);
    // my_printf("dump tous les %d\n", cor->recurence_dump);
    int idx_align_com = 0;
    for (int i = start; i < ac; i++) {
        load_champ parametres;
        parametres.a = 0;
        parametres.n = 0;
        if (!my_strcmp(av[i], "-n") && av[i + 1] && my_isnbr(av[++i]) && av[i + 1]) {
            parametres.n = 1;
            parametres.prog_nmb = my_getnbr(av[i++]);
        }
        if (!my_strcmp(av[i], "-a") && av[i + 1] && my_isnbr(av[++i]) && av[i + 1]) {
            parametres.a = 1;
            parametres.load_adress = my_getnbr(av[i++]);
        }
        parametres.filepath = av[i];
        if (!binary_to_mem(nmb_cham, parametres, cor, idx_align_com++)) {
            free(cor->mem);
            free(cor);
            return NULL;
        }
    }
    return cor;
}
