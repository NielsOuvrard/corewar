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


// ...
// add;            ok
// sub;            ok
// and;            ...
// or;             ...
// xor;            ...
// ...


// int how_many_args (command_s *com);
int how_many_args (char *list_args);

int here_other_3_reg (command_s *com)
{
    char *str = com->parametres_type;
    int nmb = 0;
    for (int i = 0; i < 3; i++)
        if (str[i] != 'r')
            return 1;
    return 0;
}

// check que les parametres sont compris entre 1 et 16

// reg , reg , reg
int fun_add     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 || here_other_3_reg(com))
        return prog->carry = 0;
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] + prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 1;
}

int fun_sub     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 || here_other_3_reg(com))
        return prog->carry = 0;
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] - prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 1;
}

// T_REG | T_DIR | T_IND,            T_REG | T_IND | T_DIR,         T_REG

// ! a modifier pour accecter les args

int fun_and     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 || com->parametres_type[2] != 'r')
        return prog->carry = 0;
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] & prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 1;
}

int fun_or      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 || com->parametres_type[2] != 'r')
        return prog->carry = 0;
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] | prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 1;
}

int fun_xor     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 || com->parametres_type[2] != 'r')
        return prog->carry = 0;
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] ^ prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 1;
}
