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

void life (prog_t *prog)
{
    my_printf("\nThe player %d(%s)is alive.\n", prog->commandes->params[1], prog->prog_name);
}

void recup_params_according_to_str (prog_t *prog)
{
    unsigned char *str = prog->binaire + prog->index;
    int index = 0, index_arr = 1;
    for (int i = 0; prog->commandes->parametres_type[i]; i++) {
        // if (prog->commandes->parametres_type[i] != ' ') {
            // my_printf("\non trouve arg %c -> %d\n", prog->commandes->parametres_type[i], (unsigned int)str[index]);
            // my_printf("index : %d\t", index);
        // }
        if (prog->commandes->parametres_type[i] == 'r') {
            prog->commandes->params[index_arr++] = (int)str[index];
            // my_printf("REG_SIZE\n");
            index += REG_SIZE;
        }
        if (prog->commandes->parametres_type[i] == 'd' &&
        prog->commandes->function != 9 && prog->commandes->function != 10) {
            prog->commandes->params[index_arr++] = char_nmb_to_int(str + index, DIR_SIZE);
            // my_printf("DIR_SIZE\n");
            index += DIR_SIZE;
        }
        if (prog->commandes->parametres_type[i] == 'i' || (prog->commandes->parametres_type[i] == 'd' &&
        (prog->commandes->function == 9 || prog->commandes->function == 10))) {
            // my_printf("IND_SIZE\n");
            prog->commandes->params[index_arr++] = char_nmb_to_int(str + index, IND_SIZE);
            index += IND_SIZE;
        }
    }
    // free(prog->commandes->parametres_type);
    prog->index += index;
}

void a_special_function (prog_t *prog)
{
    // live, zjmp, fork, lfork.
    prog->commandes->params = malloc(sizeof(int) * 2);
    prog->commandes->params[0] = 1;
    if (prog->commandes->function == 0) {
        prog->commandes->params[1] = char_nmb_to_int(prog->binaire + prog->index, DIR_SIZE);
        // life(prog);
        prog->index += DIR_SIZE;
        return;
    }
    // prog->index = 0x0fffffff;
    prog->commandes->params[1] = char_nmb_to_int(prog->binaire + prog->index, IND_SIZE);
    // my_printf("param en bit : ");
    // print_int_bits(prog->commandes->params[1]);
    // my_printf("\n ===\n");
    // print_char_bits(prog->binaire[prog->index]);
    // my_printf(" ");
    // print_char_bits(prog->binaire[prog->index + 1]);
    // my_printf("\n");
    prog->index += IND_SIZE;
    // if (prog->commandes->function == 9) {
        // 1 index
        // return;
    // }
    // if (prog->commandes->function == 12) {
        // 1 index
        // return;
    // } // 15
    // 1 index
    return;
}

void non_special_function (prog_t *prog)
{
    prog->commandes->parametres_type = type_param_to_str(prog->binaire[prog->index]);
    int nmb_args = how_many_args(prog->commandes->parametres_type);
    prog->commandes->params = malloc(sizeof(int) * (nmb_args + 1));
    prog->commandes->params[0] = nmb_args;
    char parameter_type = prog->binaire[prog->index];
    if (!parameter_type) {
        prog->index = 0x0fffffff;
        return;
    }
    // my_printf("on a à la fin `%s` car %d\n", prog->commandes->parametres_type, prog->binaire[prog->index]);
    prog->index++;
    recup_params_according_to_str(prog);
    // my_printf("nmb prog->commandes->params : %d\n", prog->commandes->params[0]);
    // for (int index_arr = 1; index_arr <= prog->commandes->params[0]; index_arr++) {
    //     my_printf("arg %d = %d\n", index_arr, prog->commandes->params[index_arr]);
    // }
}

void check_all_functions (prog_t *prog)
{
    int index;
    // prog->index = COMMENT_LENGTH;
    for (prog->index = COMMENT_LENGTH; prog->binaire[prog->index] > 0x10 ||
    prog->binaire[prog->index] < 1 &&
    prog->index < prog->size_binaire; prog->index++);
    while (prog->index < prog->size_binaire) {
        int fun_actual = prog->binaire[prog->index] - 1;
        prog->commandes = new_command(prog->commandes, fun_actual);
        op_t val = op_tab[fun_actual];
        // my_printf("command : %s\n", val.mnemonique);
        prog->index++;
        if (fun_actual == 0 || fun_actual == 8
        || fun_actual == 11 || fun_actual == 14) {
            a_special_function(prog);
        } else {
            non_special_function(prog);
        }
    }
}

prog_t *virtual_machine (char *filepath)
{
    int size = 0, first_command;
    unsigned char *str = filepath_to_str(filepath, &size);
    if (!str)
        return NULL;
    // disp_str_to_hexa(str, size);
    char *name = NULL;
    if (!check_magic(str, size, &name))
        return NULL;
    my_printf("name prog %s\n", name);
    prog_t *programme = malloc(sizeof(prog_t));
    programme->prog_name = name;
    programme->binaire = str;
    programme->size_binaire = size;
    programme->commandes = NULL;
    check_all_functions(programme);
    // disp_alls_commandes(programme);

    my_printf("\nquit VM\n");
    // free_prog(programme);
    return programme;
}
