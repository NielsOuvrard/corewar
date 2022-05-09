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

// char **file = file_cor_to_array(av[1], size);
// if (!file)
//     return 84;
// my_printf("\nle array :\n");
// for (int i = 0; file[i]; i++) {
//     if (!(i % 10))
//         my_putchar('\n');
//     my_printf("%s\t", file[i]);
// }
// free_my_arr(file);


void disp_alls_commandes (prog_t *prog)
{
    command_s *com = prog->commandes;
    my_printf("debut des commandes\n");
    while (com) {
        op_t val = op_tab[com->function];
        my_printf("com %s\nargs : ", val.mnemonique);
        for (int a = 1; a < com->params[0] + 1; a++)
            my_printf("'%d' ", com->params[a]);
        my_printf("\ncycles : %d\n\n", val.nbr_cycles);
        com = com->next;
    }
    my_printf("fin des commandes\n");
}


// command_s *new_command (command_s *old, int fun)
// {
//     command_s *new = malloc(sizeof(command_s));
//     new->function = fun;
//     new->next = NULL;
//     if (!old)
//         return new;
//     my_printf("not null! ");
//     command_s *begin = old;
//     while (old && old->next) {
//         my_printf("next");
//         old = old->next;
//     }
//     old->next = new;
//     return begin;
// }

prog_t *add_prog (prog_t *dest, prog_t *new)
{
    prog_t *begin = dest;
    if (!begin) {
        new->next = NULL;
        return new;
    }
    while (dest && dest->next)
        dest = dest->next;
    dest->next = new;
    return begin;
}

int open_programs (int ac, char **av)
{
    prog_t *list_p = NULL;
    for (int i = 1; i < ac; i++) {
        prog_t *prog = open_a_binary(av[i]);
        my_printf("prog %d : %s\n", i, av[i]);
        if (!prog)
            return 84;
        list_p = add_prog(list_p, prog);
        my_printf("ok %d\n", i);
    }
    disp_alls_commandes(list_p);
    start_cycles(list_p);
    free_alls_progs(list_p);
    // my_putstr("\n\nThe player NB_OF_PLAYER(NAME_OF_PLAYER)is alive.\n");
    // my_putstr("The player NB_OF_PLAYER(NAME_OF_PLAYER)has won.");
    // my_printf("REG_NUMBER : %d\n", REG_NUMBER);
    // my_printf("REG_SIZE : %d\n", REG_SIZE);
    return 0;
}

int main (int ac, char **av)
{
    if (ac > 1 && !my_strvcmp(av[1], "-h"))
        return help();
    if (ac < 2)
        return 1;
    return open_programs(ac, av);
}
