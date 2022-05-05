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

// brk
// sbrk

// strace

// struct a {
//     unsigned var : 7;
//     unsigned vari : 32;
//     int vari;
// };

command_s *new_command (command_s *old, int fun)
{
    command_s *new = malloc(sizeof(command_s));
    new->function = fun;
    new->next = old;
    return new;
}

void life (prog_t *prog)
{
    int nmb_player = char_nmb_to_int(prog->binaire + prog->index, 4);
    my_printf("\nThe player %d(%s)is alive.\n", nmb_player, prog->prog_name);
}

char return_type_char (char *type)
{
    if (type[0] == '0' && type[1] == '1')
        return 'r';
    if (type[0] == '1' && type[1] == '0')
        return 'd';
    if (type[0] == '1' && type[1] == '1')
        return 'i';
    return ' ';
}

char *type_param_to_str (unsigned char param)
{
    char *all_types = malloc(sizeof(char) * 5);
    all_types[4] = '\0';
    char type[3];
    type[2] = '\0';
    unsigned left_bit = 0x80;
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 2; k++) {
            type[k] = (param & left_bit) ? '1' : '0';
            param <<= 1;
        }
        all_types[i] = return_type_char(type);
    }
    return all_types;
}

void recup_params_according_to_str (prog_t *prog)
{
    unsigned char *str = prog->binaire + prog->index;
    int index = 0, index_arr = 1;
    for (int i = 0; prog->commandes->parametres_type[i]; i++) {
        my_printf("\non trouve arg %c -> %d\n", prog->commandes->parametres_type[i], (unsigned int)str[index]);
        my_printf("index : %d\n", index);
        if (prog->commandes->parametres_type[i] == 'r') {
            prog->commandes->params[index_arr++] = (int)str[index];
            index += 1;
        }
        if (prog->commandes->parametres_type[i] == 'd' &&
        prog->commandes->function != 10 && prog->commandes->function != 11) {
            prog->commandes->params[index_arr++] = char_nmb_to_int(str + index, 4);
            index += 4;
        }
        if (prog->commandes->parametres_type[i] == 'i' ||(prog->commandes->parametres_type[i] == 'd' &&
        (prog->commandes->function == 10 || prog->commandes->function == 11))) {
            prog->commandes->params[index_arr++] = char_nmb_to_int(str + index, 2);
            index += 2;
        }
    }
    prog->index += index;
}

int how_many_args (char *list_args)
{
    int size = 0;
    for (int i = 0; list_args[i]; i++) {
        if (list_args[i] != ' ')
            size++;
    }
    return size;
}

void a_special_function (prog_t *prog)
{
    // live, zjmp, fork, lfork.
    if (prog->commandes->function == 0) {
        life(prog);
        prog->index += 4;
        return;
    }
    prog->index = 0x0fffffff;
    if (prog->commandes->function == 9) {

        return;
    }
    if (prog->commandes->function == 12) {

        return;
    } // 15

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
    // prog->commandes->function
    my_printf("on a à la fin `%s` car %d\n", prog->commandes->parametres_type, prog->binaire[prog->index]);
    prog->index++;
    recup_params_according_to_str(prog);
    my_printf("nmb prog->commandes->params : %d\n", prog->commandes->params[0]);
    for (int index_arr = 1; index_arr <= prog->commandes->params[0]; index_arr++) {
        my_printf("arg %d = %d\n", index_arr, prog->commandes->params[index_arr]);
    }
}

void check_all_functions (prog_t *prog)
{
    int index;
    for (prog->index = 0; prog->binaire[prog->index] > 0x10 ||
    prog->binaire[prog->index] < 1 &&
    prog->index < prog->size_binaire; prog->index++);
    // prog->index++;
    while (prog->index < prog->size_binaire) {
        int fun_actual = prog->binaire[prog->index] - 1;
        prog->commandes = new_command(prog->commandes, fun_actual);
        // prog->fun_actual = prog->binaire[prog->index] - 1;
        op_t val = op_tab[fun_actual];
        my_printf("\ncommand : `%s` car %d\n", val.mnemonique, fun_actual);
        prog->index++;
        if (fun_actual == 0 || fun_actual == 8
        || fun_actual == 11 || fun_actual == 14) {
            a_special_function(prog);
        } else {
            non_special_function(prog);
        }
    }
}

bool compare_bit (unsigned a, unsigned b, int size)
{
    for (int i = 0; i < size; i++) {
        if ((a & 1) != (b & 1))
            return 0;
        a <<= 1;
        b <<= 1;
    }
    return 1;
}

bool check_magic (unsigned char *str, int size, char **name)
{
    for (int i = 0; i < size; i++) {
        if (compare_bit(str[i], 0xea83f3, 3 * 8)) {
            int size_name = my_strlen((char *)str + i + 3);
            (*name) = malloc(sizeof(char) * (size_name + 1));
            (*name)[size_name] = '\0';
            my_strcpy((*name), (char *)str + i + 2);
            return 1;
        }
    }
    return 0;
}

void free_prog(prog_t *prog)
{
    free(prog->binaire);
    free(prog->prog_name);
    command_s *head = prog->commandes;
    while (head) {
        command_s *tmp = head;
        head = head->next;
        free(tmp->parametres_type);
        free(tmp->params);
        free(tmp);
    }
    free(prog);
}

int virtual_machine (char *filepath)
{
    int size = 0, first_command;
    unsigned char *str = filepath_to_str(filepath, &size);
    if (!str)
        return 84;
    disp_str_to_hexa(str, size);
    char *name = NULL;
    if (!check_magic(str, size, &name))
        return 0;
    my_printf("name prog %s\n", name);
    prog_t *programme = malloc(sizeof(prog_t));
    programme->prog_name = name;
    programme->binaire = str;
    programme->size_binaire = size;
    programme->commandes = NULL;
    check_all_functions(programme);
    my_printf("quit VM\n");
    free_prog(programme);
    // char *shorter = str_but_shorter(str, size);
    return 0;
}
// my_putstr("\nen hexa :\n");
// disp_str_to_hexa(shorter, my_strlen(shorter));
// for (first_command = 0; shorter[first_command] > 0x10 ||
//      shorter[first_command] < 1; first_command++);
// op_t val = op_tab[shorter[first_command] -  1];
// my_printf("\nfirst command : %s\n en %d\n", val.mnemonique, first_command);
// find_commandes(shorter);
// for (int i = 0; shorter[i]; i++) {
//     char zero = shorter[i];
//     for (int k = 0; k < 8; k++) {
//         my_printf("%c", (zero & 1) + '0');
//         zero >>= 1;
//         if (k == 3)
//             my_putchar(' ');
//     }
//     my_printf("\n");
// }
// free(shorter);
