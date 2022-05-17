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

int how_many_cycles_for_next (unsigned char *mem, int index)
{
    if (mem[index] <= 0 || (mem[index] - 1) > 0x10) {
        return 0;
    }
    op_t val = op_tab[mem[index] - 1];
    my_printf("mem de index = %d\tça return %d\n", mem[index], val.nbr_cycles);
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
        if (expl->cycle_to_wait > 0) {
            expl->cycle_to_wait -= 16;
            my_printf("il rest %d cycle pour prog %d\n", expl->cycle_to_wait, expl->nmb_player);
        } else {
            execute_this_commande(cor, expl);
            expl->cycle_to_wait = how_many_cycles_for_next(cor->mem, expl->registres[0]);
            // my_printf("cycle to wait : %d\n", expl->cycle_to_wait);
            // dump_amll(cor);
        }
        my_printf("prog de carry : %d\n", expl->carry);

        if (!(expl->cycle_to_die--))
            cor->progs = delete_id_prog(cor->progs, id); // il décède le con
        expl = expl->next;
    }
    my_printf("cycle live %d\n", cor->cycle_to_die_init);
}

char *my_scanf (void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t lower_case = 0;
    lower_case = getline(&line, &len, stdin);
    if (lower_case < 0) {
        free(line);
        return NULL;
    }
    return line;
}

int open_programs (int ac, char **av)
{
    head_cor *cor = create_mem();
    int start = 1;
    if (!my_strcmp(av[1], "-dump") && av[2] && my_isnbr(av[2])) {
        start += 2;
        cor->recurence_dump = my_getnbr(av[2]);
    }
    my_printf("dump tous les %d\n", cor->recurence_dump);
    int idx_align_com = 0;
    for (int i = start; i < ac; i++) {
        // if (!my_strcmp(av[i], "-a"))

        if (!my_strcmp(av[i], "-n") && av[i + 1] && my_isnbr(av[++i]) && av[i + 1])
            my_printf("%d", my_getnbr(av[i++]));
        if (!binary_to_mem(ac, av[i], cor, idx_align_com++)) {
            free(cor->mem);
            free(cor);
            return 84;
        }
    }
    dump_all(cor);
    for (int cycle = 0; cycle < 50000; cycle++) {
        begin_virtual_machine(cor);
        // if (!(cycle % 300)) {
            // disp_str_to_hexa(cor->mem, cor->who, MEM_SIZE);
            // my_printf("\n", "cycle %d\n", cycle);
        // }
        char *str = my_scanf();
        if (!str) {
            free_my_head(cor);
            return 0;
        } else if (str[0] == 'a') {
            dump_all(cor);
        }
        free(str);
        my_printf("cycle : %d\n", cycle);
    }
    free_my_head(cor);
    return 0;
}
// my_putstr("\n\nThe player NB_OF_PLAYER(NAME_OF_PLAYER)is alive.\n");
// my_putstr("The player NB_OF_PLAYER(NAME_OF_PLAYER)has won.");
// my_printf("REG_NUMBER : %d\n", REG_NUMBER);
// my_printf("REG_SIZE : %d\n", REG_SIZE);

int main (int ac, char **av)
{
    if (ac > 1 && !my_strvcmp(av[1], "-h"))
        return help();
    if (ac < 2)
        return 1;
    return open_programs(ac, av);
}
