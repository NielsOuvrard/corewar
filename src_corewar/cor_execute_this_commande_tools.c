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

void my_fill_funktab(int (*tab[16])(head_cor *cor, prog_t *prog, command_s *com))
{
    tab[0] = fun_live;
    tab[1] = fun_ld;
    tab[2] = fun_st;
    tab[3] = fun_add;
    tab[4] = fun_sub;
    tab[5] = fun_and;
    tab[6] = fun_or;
    tab[7] = fun_xor;
    tab[8] = fun_zjmp;
    tab[9] = fun_ldi;
    tab[10] = fun_sti;
    tab[11] = fun_fork;
    tab[12] = fun_lld;
    tab[13] = fun_lldi;
    tab[14] = fun_lfork;
    tab[15] = fun_aff;
}

void recup_params_according_to_str (head_cor *cor, prog_t *prog, command_s *com)
{
    unsigned char *str = cor->mem + prog->pc + com->next_fun;
    int index = 0, index_arr = 1;
    for (int i = 0; com->parametres_type[i]; i++) {
        if (com->parametres_type[i] == 'r') {
            com->params[index_arr++] = (int)str[index];
            index += 1;
        }
        if (com->parametres_type[i] == 'd' &&
        com->function != 9 && com->function != 10) {
            com->params[index_arr++] = char_nmb_to_int(str, index, DIR_SIZE);
            index += DIR_SIZE;
        }
        if (com->parametres_type[i] == 'i' || (com->parametres_type[i] == 'd'
        && (com->function == 9 || com->function == 10))) {
            com->params[index_arr++] = char_nmb_to_int(str, index, IND_SIZE);
            index += IND_SIZE;
        }
    }
    com->next_fun += index;
}

// free(com->parametres_type);
// live, zjmp, fork, lfork.
void a_special_function (head_cor *cor, prog_t *prog, command_s *com)
{
    com->params = malloc(sizeof(int) * 2);
    com->params[0] = 1;
    if (com->function == 0) {
        com->params[1] =
        char_nmb_to_int(cor->mem, prog->pc + com->next_fun, DIR_SIZE);
        com->next_fun += DIR_SIZE;
        return;
    }
    com->params[1] = char_nmb_to_int(cor->mem, prog->pc + com->next_fun, IND_SIZE);
    com->next_fun += IND_SIZE;
}

// my_printf("ok here non_special_function\n");
// my_printf("params : '%s'\n", com->parametres_type);
// my_printf("on a les params : %s\n", com->parametres_type);
int non_special_function (head_cor *cor, prog_t *prog, command_s *com, int to_free)
{
    com->parametres_type = type_param_to_str(
    cor->mem[prog->pc + com->next_fun]);
    int nmb_args = how_many_args(com->parametres_type);
    com->params = malloc(sizeof(int) * (nmb_args + 1));
    com->params[0] = nmb_args;
    char parameter_type = cor->mem[prog->pc + com->next_fun];
    if (!parameter_type)
        return 0;
    com->next_fun++;
    recup_params_according_to_str(cor, prog, com);
    for (int i = 0; com->parametres_type[i] != ' ' &&
    com->parametres_type[i]; i++) {
        if (com->parametres_type[i] == 'r' &&
        (com->params[i + 1] > 16 || com->params[i + 1] < 0)) {
            prog->pc = (((prog->pc + com->next_fun)
            % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
            return 0;
        }
    }
    return 1;
}
