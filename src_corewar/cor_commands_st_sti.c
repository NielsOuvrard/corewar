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

// reg , reg / dir
// copy registres[params[1]] into param[2] (reg / ind)
// diffère selon les arguments...
// takes 2 parameters. It stores the first parameter’s value (which is a register) into
// the second (whether a register or a number).
// et modifier le who
// st r4,34 stores the content of r4 at the address PC + 34 % IDX_MOD.
// st r3,r8 copies the content of r3 into r8.
void modify_4_octets_in_memory (head_cor *cor, prog_t *prog, command_s *com,
short final_value)
{
    cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 0) %
    MEM_SIZE) +MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(
    prog->registres[com->params[1] - 1] >> 24);
    cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 1) %
    MEM_SIZE) +MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(
    prog->registres[com->params[1] - 1] >> 16);
    cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 2) %
    MEM_SIZE) +MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(
    prog->registres[com->params[1] - 1] >> 8);
    cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 3) %
    MEM_SIZE) +MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(
    prog->registres[com->params[1] - 1] >> 0);
}

int fun_st      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 2)
        return 0;
    if ((com->parametres_type[1] != 'r' && com->parametres_type[1] != 'd')
    || com->parametres_type[0] != 'r')
        return 0;
    if (com->parametres_type[0] == 'r') {
        prog->registres[com->params[1] - 1] =
        prog->registres[com->params[1] - 1];
    } else {
        unsigned short value = com->params[2];
        short final_value = value >= 0x8000 ? ( - (~(value)) - 1) : value;
        modify_4_octets_in_memory(cor, prog, com, final_value);
        for (int i = 0; i < REG_SIZE; i++)
            cor->who[(((((prog->pc) + (final_value % IDX_MOD)) + i) %
            MEM_SIZE) +MEM_SIZE) % MEM_SIZE] = prog->registres[0];
    }
    return 1;
}

// reg , reg / idx / dir , reg / dir
// my_printf("on ecrit %d en mem[%d]\n",
// last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 24),
// (((((prog->pc) + ((move2 + move3) % IDX_MOD)) + 0)
// % MEM_SIZE) + MEM_SIZE) % MEM_SIZE);
short fun_sti_move (prog_t *prog, command_s *com, int *mem_mdfy, int param)
{
    if (com->parametres_type[param] != 'r') {
        (*mem_mdfy) = 1;
        if ((unsigned short)com->params[param] >= 0x8000)
            return ( - (~(short)(com->params[param])) - 1);
        else
            return (short)(com->params[param]);
    } else {
        prog->registres[com->params[param] - 1] =
        prog->registres[com->params[1] - 1];
    }
    return 0;
}

int modfy_4_mem_sti (head_cor *cor, prog_t *prog, command_s *com,
short move)
{
    int move_initiale = prog->pc + (move % IDX_MOD);
    cor->mem[(((move_initiale + 0) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] =
    last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 24);
    cor->mem[(((move_initiale + 1) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] =
    last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 16);
    cor->mem[(((move_initiale + 2) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] =
    last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 8);
    cor->mem[(((move_initiale + 3) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] =
    last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 0);
    return move_initiale;
}

int fun_sti     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3)
        return 0;
    if ((com->parametres_type[0] != 'r') ||
        (com->parametres_type[2] != 'd' && com->parametres_type[2] != 'r'))
        return 0;
    int mem_mdfy = 0;
    short move2 = fun_sti_move(prog, com, &mem_mdfy, 2);
    short move3 = fun_sti_move(prog, com, &mem_mdfy, 3);
    if (mem_mdfy) {
        int move_initiale = modfy_4_mem_sti(cor, prog, com, move2 + move3);
        for (int i = 0; i < 4; i++)
            cor->who[(((move_initiale + i) %
            MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = prog->registres[0];
    }
    return 1;
}