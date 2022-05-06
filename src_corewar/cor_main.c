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


// void disp_alls_commandes (prog_t *prog)
// {
//     command_s *com = prog->commandes;
//     my_printf("debut des commandes\n");
//     while (com) {
//         op_t val = op_tab[com->function];
//         my_printf("com %s\nargs : ", val.mnemonique);
//         for (int a = 1; a < com->params[0] + 1; a++)
//             my_printf("'%d' ", com->params[a]);
//         my_printf("\ncycles : %d\n\n", val.nbr_cycles);
//         com = com->next;
//     }
//     my_printf("fin des commandes\n");
// }

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

head_cor *create_mem (void)
{
    head_cor *cor = malloc(sizeof(head_cor));
    cor->mem = malloc(sizeof(unsigned char) * MEM_SIZE);
    for (int i = 0; i < MEM_SIZE; i++)
        cor->mem[i] = '\0';
    cor->progs = NULL;
    return cor;
}

void my_strvcpy (unsigned char *dest, unsigned char *src,
int size, int idx_dest)
{
    for (int i = 0; i < size; i++)
        dest[idx_dest + i] = src[i];
}

bool binary_to_mem (int ac, char *filepath, head_cor *cor, int idx)
{
    prog_t *prog = open_a_binary(filepath);
    if (!prog)
        return 0;
    cor->progs = add_prog(cor->progs, prog);
    int size = 0;
    unsigned char *str = filepath_to_str(filepath, &size);
    if (!str)
        return 0;
    if (!check_magic(str, size, &prog->prog_name))
        return 0;
    prog->index = idx * (MEM_SIZE / (ac - 1));
    int decale;
    for (decale = COMMENT_LENGTH;
    str[decale] > 0x10 || str[decale] < 1 && decale < size;
    decale++);
    my_strvcpy(cor->mem, str + decale, size - decale,
    prog->index);
    free(str);
    return 1;
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
    for (int cycle = 0; cycle < 30; cycle++) {
        prog_t *expl = cor->progs;
        while (expl) {
            find_command_from_here(cor->mem, &expl->index);
            // expl->cycle++;
            expl = expl->next;
        }
    }
    // prog_t *list_p = NULL;
    // for (int i = 1; i < ac; i++) {
    //     prog_t *prog = open_a_binary(av[i]);
    //     my_printf("prog %d : %s\n", i, av[i]);
    //     if (!prog)
    //         return 84;
    //     list_p = add_prog(list_p, prog);
    //     my_printf("ok %d\n", i);
    // }
    // disp_alls_commandes(list_p);
    // start_cycles(list_p);

    disp_str_to_hexa(cor->mem, MEM_SIZE);
    prog_t *expl = cor->progs;
    while (expl) {
        my_printf("index = %d\tmap de i = %d\n", expl->index, cor->mem[expl->index]);
        expl = expl->next;
    }
    free_my_head(cor);
    // malloc MEM_SIZE
    // copy commands in mem


    // free_alls_progs(list_p);
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
