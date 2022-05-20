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
//
// args :
//

// gestion erreur fonction pas ok

// autres args pour or, xor...

int how_many_args (char *list_args);


// live;           ok
// ld;             ok (gestion d'erreur)
// ...
// st;             ok
// zjmp;           ok
// ldi;            
// sti;            ok ?
// fork;           ok (surment)
// lld;            ok
// lldi;           
// lfork;          ok (surment)
// aff;            ok

// return 0 si err

prog_t *add_prog_start (prog_t *dest, prog_t *new)
{
    new->next = NULL;
    if (!dest)
        return new;
    new->next = dest;
    return new;
}

int fun_live    (head_cor *cor, prog_t *prog, command_s *com)
{
    cor->nmb_live_cycle--;
    if (0 > cor->nmb_live_cycle) {
        cor->cycle_to_die_init -= CYCLE_DELTA;
        cor->nmb_live_cycle = NBR_LIVE;
    }
    my_printf("The player %d (%s)is alive.\n", com->params[1], prog->prog_name);
    prog->cycle_to_die = cor->cycle_to_die_init;
    return 1;
}

// ind / dir , reg
// ld 34,r3 loads the REG_SIZE bytes starting at the address PC + 34 % IDX_MOD into r3.
int fun_ld      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 2)
        return prog->carry = 0;
    if (com->params[0] <= 0 || com->params[0] > 16)
        return prog->carry = 0;
    my_printf("param 1 = %c et param 2 = %c\n", com->parametres_type[0], com->parametres_type[1]);
    if ((com->parametres_type[0] != 'i' && com->parametres_type[0] != 'd') || com->parametres_type[1] != 'r')
        return prog->carry = 0;
    // my_printf("fonction ld ok\n");
    // not the PC
    int final_value;
    if (com->parametres_type[0] == 'i') {
        unsigned int value;
        value = char_nmb_to_int(cor->mem, prog->pc + (com->params[1] % IDX_MOD), REG_SIZE);
        if (value >= 0x80000000)
            final_value = ( - (~(value)) - 1);
        else
            final_value = value;
    } else if (com->parametres_type[0] == 'd') {
        final_value = com->params[1];
    } else {
        return 0;
    }
    my_printf("ld : On met %d dans r%d\n", final_value, com->params[2]);
    prog->registres[com->params[2] - 1] = final_value;
    return prog->carry = 1;
}

// reg , reg / dir
// copy registres[params[1]] into param[2] (reg / ind)
// diffère selon les arguments...
// takes 2 parameters. It stores the first parameter’s value (which is a register) into
// the second (whether a register or a number).
// et modifier le who
// st r4,34 stores the content of r4 at the address PC + 34 % IDX_MOD.
// st r3,r8 copies the content of r3 into r8.
int fun_st      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 2)
        return 0;
    if ((com->parametres_type[1] != 'r' && com->parametres_type[1] != 'd') || com->parametres_type[0] != 'r')
        return 0;
    if (com->parametres_type[0] == 'r') {
        prog->registres[com->params[1] - 1] = prog->registres[com->params[1] - 1];
    } else {// if (com->parametres_type[1] == 'i') { // ? or ri
        unsigned short value = com->params[2];
        short final_value;
        if (value >= 0x8000)
            final_value = ( - (~(value)) - 1);
        else
            final_value = value;
        // final_value %= IDX_MOD;
        cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 0) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 24);
        cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 1) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 16);
        cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 2) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 8);
        cor->mem[(((((prog->pc) + (final_value % IDX_MOD)) + 3) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 0);
        // modify_str_with_bits(cor->mem + (prog->pc + (final_value)), prog->registres[com->params[1] - 1]);
        for (int i = 0; i < REG_SIZE; i++)
            cor->who[(((((prog->pc) + (final_value % IDX_MOD)) + i) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = prog->registres[0];
    }
    return 1;
}

int fun_zjmp    (head_cor *cor, prog_t *prog, command_s *com)
{
    if (!prog->carry)
        return (com->next_fun = 3) ? 0 : 0;
    short move;
    my_printf("param : %d\n", com->params[1]);
    if ((unsigned short)com->params[1] >= 0x8000) {
        move = ( - (~(short)(com->params[1])) - 1) % IDX_MOD;
    } else {
        move = (short)(com->params[1] % IDX_MOD);
    }
    my_printf("on mode de %d\n", move);
    prog->pc = (((prog->pc + move) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    com->next_fun = 0;
    return 1;
}

// idx               idx             reg
// REG DIR IND,      DIR REG,        REG
int fun_ldi     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3)
        return prog->carry = 0;
    if ((com->parametres_type[1] != 'd' && com->parametres_type[1] != 'r') || com->parametres_type[2] != 'r')
        return prog->carry = 0;
    unsigned int s = char_nmb_to_int(
    cor->mem, prog->pc + (com->params[1] % IDX_MOD), IND_SIZE) + com->params[2];
    prog->pc = ((char_nmb_to_int(cor->mem, prog->registres[0] + (s % IDX_MOD), REG_SIZE) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    prog->carry = 1;

    // ldi 3,%4,r1 reads IND_SIZ bytes from the address PC + 3 % IDX_MOD, adds 4 to this value.
    // The sum is named S.
    // REG_SIZE bytes are read from the address PC + S % IDX_MOD and copied into r1.
    return 1;
}

// reg , reg / idx / dir , reg / dir
int fun_sti     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3)
        return 0;
    if ((com->parametres_type[0] != 'r') ||
        (com->parametres_type[2] != 'd' && com->parametres_type[2] != 'r'))
        return 0;
    short move2 = 0, move3 = 0, mem_mdfy = 0;
    if (com->parametres_type[2] != 'r') {
        if ((unsigned short)com->params[2] >= 0x8000)
            move2 = ( - (~(short)(com->params[2])) - 1);
        else
            move2 = (short)(com->params[2]);
        mem_mdfy = 1;
    } else {
        prog->registres[com->params[2] - 1] = prog->registres[com->params[2] - 1];
    }
    if (com->parametres_type[3] != 'r') {
        if ((unsigned short)com->params[3] >= 0x8000)
            move3 = ( - (~(short)(com->params[3])) - 1);
        else
            move3 = (short)(com->params[3]);
        mem_mdfy = 1;
    } else {
        prog->registres[com->params[3] - 1] = prog->registres[com->params[3] - 1];
    }
    if (mem_mdfy) {
        int move_initiale = prog->pc + ((move2 + move3) % IDX_MOD);
        my_printf("on ecrit %d en mem[%d]\n", last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 24), (((((prog->pc) + ((move2 + move3) % IDX_MOD)) + 0) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE);
        cor->mem[(((move_initiale + 0) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 24);
        cor->mem[(((move_initiale + 1) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 16);
        cor->mem[(((move_initiale + 2) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 8);
        cor->mem[(((move_initiale + 3) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = last_octet_int_to_char(prog->registres[com->params[1] - 1] >> 0);
        for (int i = 0; i < 4; i++)
            cor->who[(((move_initiale + i) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE] = prog->registres[0];
    }
    return 1;
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
    // my_printf("prog name = %s\n", prog->prog_name);
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
    // idx
    // It creates a new program that inherits different states from the parent.
    // This program is executed at the address PC + first parameter % IDX_MOD.
    return 1;
}

// DIR | IND, REG
int fun_lld     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3)        // 3 args ?
        return prog->carry = 0;
    if ((com->parametres_type[1] != 'r') ||
        (com->parametres_type[0] != 'd' && com->parametres_type[0] != 'i'))
        return prog->carry = 0;
    int final_value;
    if (com->parametres_type[0] == 'i') {
        unsigned int value;
        value = char_nmb_to_int(cor->mem, prog->pc + (com->params[1]), REG_SIZE);
        if (value >= 0x80000000)
            final_value = ( - (~(value)) - 1);
        else
            final_value = value;
    } else if (com->parametres_type[0] == 'd') {
        final_value = com->params[1];
    } else {
        return prog->carry = 0;
    }
    prog->registres[com->params[2] - 1] = final_value;
    return prog->carry = 1;
}

// idx               idx             reg
// REG DIR IND,      DIR REG,        REG
int fun_lldi    (head_cor *cor, prog_t *prog, command_s *com)
{
    if (how_many_args(com->parametres_type) != 3)    // args ?
        return prog->carry = 0;
    if ((com->parametres_type[2 - 1] != 'd' && com->parametres_type[2 - 1] != 'r') || com->parametres_type[3 - 1] != 'r')
        return prog->carry = 0;
    if ((com->parametres_type[2 - 1] != 'r') ||
        (com->parametres_type[1 - 1] != 'd' && com->parametres_type[1 - 1] != 'i'))
        return prog->carry = 0;
    unsigned int s = char_nmb_to_int(cor->mem, prog->pc + com->params[1], IND_SIZE) + com->params[2];
    prog->pc = char_nmb_to_int(cor->mem, prog->pc + s, REG_SIZE);
    prog->carry = 1;
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
