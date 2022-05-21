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

// ind / dir , reg
// ld 34,r3 loads the REG_SIZE bytes starting at the address PC + 34 % IDX_MOD into r3.
int fun_ld      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 2)
        return prog->carry = 0;
    if (com->params[0] <= 0 || com->params[0] > 16)
        return prog->carry = 0;
    if ((com->parametres_type[0] != 'i' &&
    com->parametres_type[0] != 'd') || com->parametres_type[1] != 'r')
        return prog->carry = 0;
    int final_value;
    if (com->parametres_type[0] == 'i') {
        unsigned int value;
        value = char_nmb_to_int(
        cor->mem, prog->pc + (com->params[1] % IDX_MOD), REG_SIZE);
        final_value = value >= 0x80000000 ? ( - (~(value)) - 1) : value;
    } else if (com->parametres_type[0] == 'd') {
        final_value = com->params[1];
    } else {
        return 0;
    }
    prog->registres[com->params[2] - 1] = final_value;
    return prog->carry = 1;
}

// DIR | IND, REG
int fun_lld     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 2)
        return prog->carry = 0;
    if (com->params[0] <= 0 || com->params[0] > 16)
        return prog->carry = 0;
    if ((com->parametres_type[0] != 'i' &&
    com->parametres_type[0] != 'd') || com->parametres_type[1] != 'r')
        return prog->carry = 0;
    int final_value;
    if (com->parametres_type[0] == 'i') {
        unsigned int value;
        value = char_nmb_to_int(
        cor->mem, prog->pc + (com->params[1]), REG_SIZE);
        final_value = value >= 0x80000000 ? ( - (~(value)) - 1) : value;
    } else if (com->parametres_type[0] == 'd') {
        final_value = com->params[1];
    } else {
        return 0;
    }
    prog->registres[com->params[2] - 1] = final_value;
    return prog->carry = 1;
}
