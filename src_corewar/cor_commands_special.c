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
int fun_live    (head_cor *cor, prog_t *prog, command_s *com)
{
    cor->nmb_live_cycle--;
    if (0 > cor->nmb_live_cycle) {
        cor->cycle_to_die_init -= CYCLE_DELTA;
        cor->nmb_live_cycle = NBR_LIVE;
    }
    my_printf("The player %d (%s)is alive.\n",
    com->params[1], prog->prog_name);
    prog->cycle_to_die = cor->cycle_to_die_init;
    return 1;
}

// my_printf("on mode de %d\n", move);
int fun_zjmp    (head_cor *cor, prog_t *prog, command_s *com)
{
    if (!prog->carry)
        return (com->next_fun = 3) ? 0 : 0;
    short move;
    if ((unsigned short)com->params[1] >= 0x8000) {
        move = ( - (~(short)(com->params[1])) - 1) % IDX_MOD;
    } else {
        move = (short)(com->params[1] % IDX_MOD);
    }
    prog->pc = (((prog->pc + move) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    com->next_fun = 0;
    return 1;
}
