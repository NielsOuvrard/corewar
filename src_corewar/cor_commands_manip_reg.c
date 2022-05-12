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
// and;            ok
// or;             ok
// xor;            ok
// ...

// reg , reg , reg
int fun_add     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] + prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 0;
}

int fun_sub     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] - prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 0;
}

int fun_and     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] & prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 0;
}

int fun_or      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] | prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 0;
}

int fun_xor     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr"))
        return prog->carry = 0;
    prog->registres[com->params[3] - 1] =
    prog->registres[com->params[1] - 1] ^ prog->registres[com->params[2] - 1];
    prog->carry = 1;
    return 0;
}
