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
    if (mem[index] - 1 == 0 || mem[index] - 1 > 0x10) {
        return 0;
    }
    op_t val = op_tab[mem[index] - 1];
    return val.nbr_cycles;
}

void begin_virtual_machine (head_cor *cor)
{
    prog_t *expl = cor->progs;
    while (expl) {
        if (expl->cycle_to_wait) {
            expl->cycle_to_wait--;
        } else {
            execute_this_commande(cor, expl);
            expl->cycle_to_wait = how_many_cycles_for_next(cor->mem, expl->registres[0]);
            // my_printf("cycle to wait : %d\n", expl->cycle_to_wait);
            // dump_amll(cor);
        }
        expl = expl->next;
    }
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
    int idx_align_com = 0;
    for (int i = 1; i < ac; i++) {
        if (!binary_to_mem(ac, av[i], cor, idx_align_com++)) {
            free(cor->mem);
            free(cor);
            return 84;
        }
    }
    dump_all(cor);
    for (int cycle = 0; cycle < 5000; cycle++) {
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
        cycle += 9;
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
