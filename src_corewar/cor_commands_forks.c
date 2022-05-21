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

// bonus :
// affichage
// dump plus de précision (nmb de octet / lignes) (binaire, decimal)
int how_many_args (char *list_args);

prog_t *add_prog_start (prog_t *dest, prog_t *new)
{
    new->next = NULL;
    if (!dest)
        return new;
    new->next = dest;
    return new;
}

int fun_fork    (head_cor *cor, prog_t *prog, command_s *com)
{
    prog_t *new_prog = malloc(sizeof(prog_t));
    new_prog->carry = 1;
    new_prog->cycle_to_wait = 0;
    new_prog->cycle_to_die = cor->cycle_to_die_init;
    new_prog->registres = malloc(sizeof(int) * 16);
    for (int i = 1; i < 16; i++)
        new_prog->registres[i] = 0;
    new_prog->registres[0] = prog->registres[0];
    new_prog->prog_name = my_strdup(prog->prog_name);
    new_prog->next = NULL;
    cor->progs = add_prog_start(cor->progs, new_prog);
    short move;
    if ((unsigned short)com->params[1] >= 0x8000) {
        move = ( - (~(short)(com->params[1])) - 1) % IDX_MOD;
    } else {
        move = (short)(com->params[1] % IDX_MOD);
    }
    new_prog->pc = (((prog->pc + move) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    return 1;
}

int fun_lfork   (head_cor *cor, prog_t *prog, command_s *com)
{
    prog_t *new_prog = malloc(sizeof(prog_t));
    new_prog->carry = 1;
    new_prog->cycle_to_wait = 0;
    new_prog->cycle_to_die = cor->cycle_to_die_init;
    new_prog->registres = malloc(sizeof(int) * 16);
    for (int i = 1; i < 16; i++)
        new_prog->registres[i] = 0;
    new_prog->registres[0] = prog->registres[0];
    new_prog->next = NULL;
    new_prog->prog_name = my_strdup(prog->prog_name);
    cor->progs = add_prog_start(cor->progs, new_prog);
    short move;
    if ((unsigned short)com->params[1] >= 0x8000) {
        move = ( - (~(short)(com->params[1])) - 1);
    } else {
        move = (short)(com->params[1]);
    }
    new_prog->pc = (((prog->pc + move) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    return 1;
}

// reg
int fun_aff     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 1 || com->params[1] != 'r')
        return 0;
    my_printf("%d\n", prog->registres[com->params[1] - 1] % 256);
    return 1;
}
