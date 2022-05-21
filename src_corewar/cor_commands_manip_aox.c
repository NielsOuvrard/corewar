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

int fun_and     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 ||
    com->parametres_type[2] != 'r')
        return prog->carry = 0;
    int v1 = 0, v2 = 0;
    if (com->parametres_type[0] == 'r') {
        v1 = prog->registres[com->params[1] - 1];
    } else if (com->parametres_type[0] == 'd') {
        v1 = char_nmb_to_int(cor->mem, prog->pc + com->params[1], IND_SIZE);
    } else {
        v1 = char_nmb_to_int(cor->mem, prog->pc + com->params[1], DIR_SIZE);
    }
    if (com->parametres_type[1] == 'r') {
        v2 = prog->registres[com->params[2] - 1];
    } else if (com->parametres_type[1] == 'd') {
        v2 = char_nmb_to_int(cor->mem, prog->pc + com->params[2], IND_SIZE);
    } else {
        v2 = char_nmb_to_int(cor->mem, prog->pc + com->params[2], DIR_SIZE);
    }
    prog->registres[com->params[3] - 1] = v1 & v2;
    return prog->carry = 1;
}

int fun_or      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 ||
    com->parametres_type[2] != 'r')
        return prog->carry = 0;
    int v1 = 0, v2 = 0;
    if (com->parametres_type[0] == 'r') {
        v1 = prog->registres[com->params[1] - 1];
    } else if (com->parametres_type[0] == 'd') {
        v1 = char_nmb_to_int(cor->mem, prog->pc + com->params[1], IND_SIZE);
    } else {
        v1 = char_nmb_to_int(cor->mem, prog->pc + com->params[1], DIR_SIZE);
    }
    if (com->parametres_type[1] == 'r') {
        v2 = prog->registres[com->params[2] - 1];
    } else if (com->parametres_type[1] == 'd') {
        v2 = char_nmb_to_int(cor->mem, prog->pc + com->params[2], IND_SIZE);
    } else {
        v2 = char_nmb_to_int(cor->mem, prog->pc + com->params[2], DIR_SIZE);
    }
    prog->registres[com->params[3] - 1] = v1 | v2;
    return prog->carry = 1;
}

int fun_xor     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3 ||
    com->parametres_type[2] != 'r')
        return prog->carry = 0;
    int v1 = 0, v2 = 0;
    if (com->parametres_type[0] == 'r') {
        v1 = prog->registres[com->params[1] - 1];
    } else if (com->parametres_type[0] == 'd') {
        v1 = char_nmb_to_int(cor->mem, prog->pc + com->params[1], IND_SIZE);
    } else {
        v1 = char_nmb_to_int(cor->mem, prog->pc + com->params[1], DIR_SIZE);
    }
    if (com->parametres_type[1] == 'r') {
        v2 = prog->registres[com->params[2] - 1];
    } else if (com->parametres_type[1] == 'd') {
        v2 = char_nmb_to_int(cor->mem, prog->pc + com->params[2], IND_SIZE);
    } else {
        v2 = char_nmb_to_int(cor->mem, prog->pc + com->params[2], DIR_SIZE);
    }
    prog->registres[com->params[3] - 1] = v1 ^ v2;
    return prog->carry = 1;
}
