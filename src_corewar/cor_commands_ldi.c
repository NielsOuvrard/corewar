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

// the first two must be index
// idx               idx             reg
// REG DIR IND,      DIR REG,        REG
int fun_ldi     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3)
        return prog->carry = 0;
    if ((com->parametres_type[1] != 'd' && com->parametres_type[1] != 'i') ||
        (com->parametres_type[2] != 'd' && com->parametres_type[2] != 'i') ||
        com->parametres_type[3] != 'r')
        return prog->carry = 0;
    unsigned int s = char_nmb_to_int(
    cor->mem, prog->pc + (com->params[1] %
    IDX_MOD), IND_SIZE) + com->params[2];
    prog->registres[com->params[3] - 1] = ((char_nmb_to_int(cor->mem,
    prog->registres[0] + (s % IDX_MOD), REG_SIZE)
    % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    return prog->carry = 1;
}

int fun_lldi    (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3)
        return prog->carry = 0;
    if ((com->parametres_type[1] != 'd' && com->parametres_type[1] != 'i') ||
        (com->parametres_type[2] != 'd' && com->parametres_type[2] != 'i') ||
        com->parametres_type[3] != 'r')
        return prog->carry = 0;
    unsigned int s = char_nmb_to_int(
    cor->mem, prog->pc + (com->params[1]), IND_SIZE) + com->params[2];
    prog->registres[com->params[3] - 1] = ((char_nmb_to_int(cor->mem,
    prog->registres[0] + (s), REG_SIZE) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    prog->carry = 1;
    return 1;
}
