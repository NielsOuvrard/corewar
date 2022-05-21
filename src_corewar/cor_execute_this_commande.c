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

void my_fill_funktab(int (*tab[16])(head_cor *cor, prog_t *prog, command_s *com));

void recup_params_according_to_str (head_cor *cor, prog_t *prog, command_s *com);

void a_special_function (head_cor *cor, prog_t *prog, command_s *com);

int non_special_function (head_cor *cor, prog_t *prog, command_s *com, int to_free);

void disp_infos_com (prog_t *prog, command_s *com, op_t val)
{
    my_printf("\033[%dmprog %d ", 97 - prog->registres[0], prog->registres[0]);
    my_printf("PC = %d\n", prog->pc);
    my_printf("com %s%s%s\n", MY_COLOR_GREEN, val.mnemonique, MY_COLOR_RESET);
    my_printf("args : ");
    for (int a = 1; a < com->params[0] + 1; a++)
        my_printf("'%d' ", com->params[a]);
    my_printf("\n");
}

int free_this_commande (head_cor *cor, prog_t *prog, command_s *com,
int to_free)
{
    if (to_free)
        free(com->parametres_type);
    free(com->params);
    free(com);
    return 0;
}

void exec_prt_funct (head_cor *cor, prog_t *prog, command_s *com, int funct)
{
    int (*tab[16])(head_cor *cor, prog_t *prog, command_s *com);
    my_fill_funktab(tab);
    if (!tab[funct](cor, prog, com))
        com->next_fun = 1;
    prog->pc = (((prog->pc + com->next_fun) %
    MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
}

void execute_this_commande (head_cor *cor, prog_t *prog)
{
    if (!cor->mem[prog->pc] || cor->mem[prog->pc] > 17) {
        prog->pc = (((prog->pc + 1) % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
        return;
    }
    if (cor->who[prog->pc] != 0 && cor->who[prog->pc] != prog->registres[0])
        return;
    int funct = cor->mem[(prog->pc)] - 1;
    command_s *com = malloc(sizeof(command_s));
    com->function = funct;
    com->next_fun = 1;
    op_t val = op_tab[funct];
    int to_free = 0;
    if (funct == 0 || funct == 8 || funct == 11 || funct == 14)
        a_special_function(cor, prog, com);
    else if (!non_special_function(cor, prog, com, to_free = 1))
        return;
    exec_prt_funct(cor, prog, com, funct);
    if (cor->more_infos)
        disp_infos_com(prog, com, val);
    free_this_commande(cor, prog, com, to_free);
}
