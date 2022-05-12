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


// live;           
// ld;             ok
// ...
// zjmp;           ok
// ldi;            
// sti;            
// fork;           
// lld;            
// lldi;           
// lfork;          
// aff;            

int fun_live    (head_cor *cor, prog_t *prog, command_s *com)
{
    my_printf("The player %d (%s)is alive.\n",
    com->params[0], prog->prog_name);
    // ! delta -= cylcle...
    return 0;
}

// ind / dir , reg
// ld 34,r3 loads the REG_SIZE bytes starting at the address PC + 34 % IDX_MOD into r3.
int fun_ld      (head_cor *cor, prog_t *prog, command_s *com)
{
    int final_value;
    if (com->parametres_type[1] == 'i') {
        unsigned int value;
        value = char_nmb_to_int(cor->mem + prog->registres[0] + (com->params[1] % IDX_MOD), REG_SIZE);
        if (value >= 0x80000000)
            final_value = ( - (~(value)) - 1);
        else
            final_value = value;
    } else if (com->parametres_type[1] == 'd') {
        final_value = com->params[1];
    } else {
        return prog->carry = 0;
    }
    my_printf("ld : On met %d dans r%d\n", final_value, com->params[2]);
    prog->registres[com->params[2] - 1] = final_value;
    prog->carry = 1;
    return 0;
}

// reg , reg / dir
// copy registres[params[1]] into param[2] (reg / ind)
int fun_st      (head_cor *cor, prog_t *prog, command_s *com)
{
    // diffère selon les arguments...
    // takes 2 parameters. It stores the first parameter’s value (which is a register) into
    // the second (whether a register or a number).
    if (com->parametres_type[2] == 'r') {
        prog->registres[com->params[2] - 1] = prog->registres[com->params[1] - 1];
    } else if (com->parametres_type[2] == 'i') { // ? or ri
        unsigned short value = com->params[2];
        short final_value;
        if (value >= 0x8000)
            final_value = ( - (~(value)) - 1);
        else
            final_value = value;
        final_value %= IDX_MOD;
        modify_str_with_bits(cor->mem + (prog->registres[0] + (final_value)), prog->registres[com->params[1] - 1]);
    } else {
        return 0;
    }
    // et modifier le who
    // st r4,34 stores the content of r4 at the address PC + 34 % IDX_MOD.
    // st r3,r8 copies the content of r3 into r8.
    return 0;
}

int fun_zjmp    (head_cor *cor, prog_t *prog, command_s *com)
{
    if (!prog->carry)
        return com->next_fun = 3;
    short move;
    if (com->params[1] >= 0x8000) {
        move = ( - (~(short)(com->params[1])) - 1) % IDX_MOD;
    } else {
        move = (short)(com->params[1] % IDX_MOD);
    }
    prog->registres[0] += move;
    com->next_fun = 0;
    return 0;
}

// REG DIR IND,      DIR REG,        REG
int fun_ldi     (head_cor *cor, prog_t *prog, command_s *com)
{
    unsigned int s = char_nmb_to_int(cor->mem + prog->registres[0] + (com->params[1] % IDX_MOD), IND_SIZE) + com->params[2];
    prog->registres[0] = char_nmb_to_int(cor->mem + prog->registres[0] + (s % IDX_MOD), REG_SIZE);
    // * This operation modifies the carry.
    prog->carry = 1; // pourquoi pas
    // ldi 3,%4,r1 reads IND_SIZ bytes from the address PC + 3 % IDX_MOD, adds 4 to this value.
    // Thesumisnamed S.
    // REG_SIZE bytes arereadfromtheaddress PC + S % IDX_MODandcopiedintor1.
    return 0;
}

int fun_sti     (head_cor *cor, prog_t *prog, command_s *com)
{
    // reg , reg / idx , reg / idx
    my_printf("index %d on ecrit en %d soit %d après l'index\n", prog->registres[0], prog->registres[0] + ((com->params[2] + com->params[3]) % IDX_MOD),
    ((com->params[2] + com->params[3]) % IDX_MOD));
    my_printf("et on ecrit :");
    print_int_bits(prog->registres[com->params[1] - 1]);
    my_printf("\n");
    modify_str_with_bits(cor->mem + prog->registres[0] + ((com->params[2] + com->params[3]) % IDX_MOD), prog->registres[com->params[1] - 1]);
    for (int i = 0; i < 4; i++)
        cor->who[prog->registres[0] + ((com->params[2] + com->params[3]) % IDX_MOD) + i] = prog->nmb_player;

    // sti r2,%4,%5 copies the contentof r2 into the address PC + (4+5) % IDX_MOD.
    // prog->registres[com->params[1]];
    return 0;
}

int fun_fork    (head_cor *cor, prog_t *prog, command_s *com)
{
    // idx
    // !!! new prog = prog->registres[0] + (com->params[1] % IDX_MOD);
    // It creates a new program that inherits different states from the parent.
    // This program is executed at the address PC + first parameter % IDX_MOD.
    return 0;
}

int fun_lld     (head_cor *cor, prog_t *prog, command_s *com)
{
    int index = prog->registres[0] + com->params[1];
    unsigned int value = char_nmb_to_int(cor->mem + index, REG_SIZE);
    my_printf("ld : On met %d dans r%d\n", value, com->params[2]);
    prog->registres[com->params[2] - 1] = value;
    // * This operation modifies the carry.
    prog->carry = 1; // pourquoi pas
    return 0;
}

int fun_lldi    (head_cor *cor, prog_t *prog, command_s *com)
{
    unsigned int s = char_nmb_to_int(cor->mem + prog->registres[0] + com->params[1], IND_SIZE) + com->params[2];
    prog->registres[0] = char_nmb_to_int(cor->mem + prog->registres[0] + s, REG_SIZE);
    // * This operation modifies the carry.
    prog->carry = 1; // pourquoi pas
    return 0;
}

int fun_lfork   (head_cor *cor, prog_t *prog, command_s *com)
{
    // !!! new prog = prog->registres[0] + com->params[1];
    return 0;
}

int fun_aff     (head_cor *cor, prog_t *prog, command_s *com)
{
    // reg
    my_printf("%d\n", prog->registres[com->params[1] - 1] % 256);
    // It displays on the standard output the character whose ASCII code is the content of the register (in base 10).
    // A 256 modulo is applied to this ASCII code.
    // aff r3 displays ’*’ if r3 contains 42.
    return 0;
}

// il manque fork et lfork