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

int fun_live    (head_cor *cor, prog_t *prog, command_s *com)
{
    my_printf("The player %d (%s)is alive.\n",
    com->params[0], prog->prog_name);
    // ! delta -= cylcle...
    return 0;
}

int fun_ld      (head_cor *cor, prog_t *prog, command_s *com)
{
    int index = prog->registres[0] + (com->params[1] % IDX_MOD);
    unsigned int value = char_nmb_to_int(cor->mem + index, REG_SIZE);
    my_printf("ld : On met %d dans r%d\n", value, com->params[2]);
    prog->registres[com->params[2] - 1] = value;
    // * This operation modifies the carry.
    prog->carry = 1; // pourquoi pas
    // prog->registres[com->params[2]] = com->params[1];
    // valeure de param 1 dans param 2
    // ld 34,r3 loads the REG_SIZE bytes starting at the address PC + 34 % IDX_MOD into r3.
    // com->parametres_type;
    // com->params;
    return 0;
}

int fun_st      (head_cor *cor, prog_t *prog, command_s *com)
{
    // diffère selon les arguments...
    // reg , reg / dir
    // takes 2 parameters. It stores the first parameter’s value (which is a register) into
    // the second (whether a register or a number).

    if (!my_strcmp(com->parametres_type, "rr")) {
        prog->registres[com->params[2] - 1] = prog->registres[com->params[1] - 1];
    } else if (!my_strcmp(com->parametres_type, "rd")) { // ? or ri
        prog->registres[com->params[2] - 1] = char_nmb_to_int(
        cor->mem + (prog->registres[0] + (com->params[1] % IDX_MOD)), REG_SIZE);
    }
    // param 2 = r[param 1];
    // modify_str_with_bits(cor->mem + )
    // et modifier le who
    // st r4,34 stores the content of r4 at the address PC + 34 % IDX_MOD.
    modify_str_with_bits(cor->mem + (prog->registres[0] + (com->params[2] % IDX_MOD)), prog->registres[com->params[1] - 1]);
    // st r3,r8 copies the content of r3 into r8.
    return 0;
}

int fun_add     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr") && my_strcmp(com->parametres_type, " rrr"))
        return 1;
    prog->registres[com->params[3] - 1] = prog->registres[com->params[1] - 1] + prog->registres[com->params[2] - 1];
    // takes 3 registers as parameters. It adds the content of the first two and puts the sum
    // into the third one (which must be a register).
    // * This operation modifies the carry.
    prog->carry = 1; // pourquoi pas
    // add r2,r3,r5addsthecontentofr2andr3andputstheresultintor5.
    return 0;
}

int fun_sub     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr") && my_strcmp(com->parametres_type, " rrr"))
        return 1;
    prog->registres[com->params[3] - 1] = prog->registres[com->params[1] - 1] - prog->registres[com->params[2] - 1];
    // Similar to add, but performing a subtraction.
    // takes 3 parameters. It performs a binary AND between the first two parameters
    // and stores the result into the third one (which must be a register).
    // * This operation modifies the carry.
    prog->carry = 1; // pourquoi pas
    // and r2, %0,r3 puts r2 & 0 into r3.
    return 0;
}

int fun_and     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr") && my_strcmp(com->parametres_type, " rrr"))
        return 1;
    prog->registres[com->params[3] - 1] = prog->registres[com->params[1] - 1] & prog->registres[com->params[2] - 1];        // vraiment ça ?
    return 0;
}

int fun_or      (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr") && my_strcmp(com->parametres_type, " rrr"))
        return 1;
    prog->registres[com->params[3] - 1] = prog->registres[com->params[1] - 1] | prog->registres[com->params[2] - 1];
    return 0;
}

int fun_xor     (head_cor *cor, prog_t *prog, command_s *com)
{
    if (my_strcmp(com->parametres_type, "rrr") && my_strcmp(com->parametres_type, " rrr"))
        return 1;
    prog->registres[com->params[3] - 1] = prog->registres[com->params[1] - 1] ^ prog->registres[com->params[2] - 1];
    return 0;
}

int fun_zjmp    (head_cor *cor, prog_t *prog, command_s *com)
{
    // if (my_strcmp(com->parametres_type, "i") || !prog->carry)   // check param type au deuxime duo de bit
    //     return 1;

    // if carry == 1, jump to this


    // nombres neg
    short move;
    my_printf("\n");
    if (com->params[1] >= 0x8000) {
        my_printf("neg");
        move = ( - (~(short)(com->params[1])) - 1) % IDX_MOD;
    } else {
        move = (short)(com->params[1] % IDX_MOD);
    }
    my_printf("on bouge de %d\n", move);
    my_printf("prog de reg O = %d\n", prog->registres[0]);
    prog->registres[0] += move;
    my_printf("prog de reg O = %d\n", prog->registres[0]);
    com->next_fun = 0;
    // It jumps to this index if the carry is worth 1.
    // Other wise, it does nothing but consumes the same time.
    // zjmp %23 puts,if carry equals 1, PC + 23 % IDX_MOD in to the PC.
    return 0;
}

int fun_ldi     (head_cor *cor, prog_t *prog, command_s *com)
{
    // index index reg
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