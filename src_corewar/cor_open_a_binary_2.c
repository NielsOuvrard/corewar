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

// void life (prog_t *prog)
// {
//     // my_printf("\nThe player %d(%s)is alive.\n", prog->commandes->params[1], prog->prog_name);
// }

void recup_params_according_to_str (unsigned char *mem, int *index_param, command_s *com)
{
    unsigned char *str = mem + (*index_param);
    int index = 0, index_arr = 1;
    for (int i = 0; com->parametres_type[i]; i++) {
        if (com->parametres_type[i] == 'r') {
            com->params[index_arr++] = (int)str[index];
            index += 1;
        }
        if (com->parametres_type[i] == 'd' &&
        com->function != 9 && com->function != 10) {
            com->params[index_arr++] = char_nmb_to_int(str + index, DIR_SIZE);
            index += DIR_SIZE;
        }
        if (com->parametres_type[i] == 'i' || (com->parametres_type[i] == 'd'
        && (com->function == 9 || com->function == 10))) {
            com->params[index_arr++] = char_nmb_to_int(str + index, IND_SIZE);
            index += IND_SIZE;
        }
    }
    (*index_param) += index;
}
// free(com->parametres_type);

// live, zjmp, fork, lfork.
void a_special_function (unsigned char *mem, int *index, command_s *com)
{
    com->params = malloc(sizeof(int) * 2);
    com->params[0] = 1;
    if (com->function == 0) {
        com->params[1] =
        char_nmb_to_int(mem + (*index), DIR_SIZE);
        (*index) += DIR_SIZE;
        return;
    }
    com->params[1] = char_nmb_to_int(mem + (*index), IND_SIZE);
    (*index) += IND_SIZE;
}

void non_special_function (unsigned char *mem, int *index, command_s *com)
{
    com->parametres_type = type_param_to_str(mem[(*index)]);
    my_printf("on a les params : %s\n", com->parametres_type);
    int nmb_args = how_many_args(com->parametres_type);
    com->params = malloc(sizeof(int) * (nmb_args + 1));
    com->params[0] = nmb_args;
    char parameter_type = mem[(*index)];
    if (!parameter_type) {
        // index = 0x0fffffff;
        return;
    }
    (*index)++;
    recup_params_according_to_str(mem, index, com);
    free(com->parametres_type);
}

void find_command_from_here (unsigned char *mem, int *index)
{
    if (!mem[*index])
        return;
    int fun_actual = mem[(*index)] - 1;
    command_s *com = malloc(sizeof(command_s));
    com->function = fun_actual;
    // command_s *com = new_command(prog->commandes, fun_actual);
    // if (!prog->commandes)
    //     prog->commandes = com;
    (*index)++;
    op_t val = op_tab[fun_actual];
    if (fun_actual == 0 || fun_actual == 8 || fun_actual == 11 || fun_actual == 14) {
        a_special_function(mem, index, com);
    } else {
        non_special_function(mem, index, com);
    }
    // op_t val = op_tab[com->function];

    my_printf("com %s%s%s\nargs : ", MY_COLOR_GREEN, val.mnemonique, MY_COLOR_RESET);
    for (int a = 1; a < com->params[0] + 1; a++)
        my_printf("'%d' ", com->params[a]);
    my_printf("\ncycles : %d\n\n", val.nbr_cycles);
    free(com->params);
    free(com);
}

// void check_all_functions (prog_t *prog)
// {
    // int index;
    // for (prog->index = COMMENT_LENGTH; prog->binaire[prog->index] > 0x10 ||
    // prog->binaire[prog->index] < 1 &&
    // prog->index < prog->size_binaire; prog->index++);
    // while (prog->index < prog->size_binaire) {
        // int fun_actual = prog->binaire[prog->index] - 1;
        // command_s *com = new_command(prog->commandes, fun_actual);
        // if (!prog->commandes)
        //     prog->commandes = com;
        // op_t val = op_tab[fun_actual];
        // prog->index++;
        // if (fun_actual == 0 || fun_actual == 8
        // || fun_actual == 11 || fun_actual == 14) {
        //     a_special_function(prog, com);
        // } else {
        //     non_special_function(prog, com);
        // }
    // }
// }

// disp_str_to_hexa(str, size);
    // int size = 0, first_command;
    // unsigned char *str = filepath_to_str(filepath, &size);
    // if (!str)
    //     return NULL;
    // char *name = NULL;
    // if (!check_magic(str, size, &name))
    //     return NULL;
    // my_printf("name prog %s\n", name);

    // programme->binaire = str;
    // programme->size_binaire = size;
    // programme->commandes = NULL;
    // check_all_functions(programme);
    // my_printf("\nquit VM\n");
