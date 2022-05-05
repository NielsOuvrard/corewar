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
    // int vari;
// };

int modify_bit_n_in_int (int nmb, int where, bool bit)
{
    if (bit)
        return nmb | (1u << where);
    return nmb ^ (1u << where);
}

void print_char_bits (unsigned char c){
    unsigned char left = 1 << 7;
    for (char i = 0; i < 8; i++){
        my_putchar((c & left) ? '1' : '0');
        c <<= 1;
    }
}

void print_int_bits (unsigned int num){
    unsigned int left = 1 << 31;
    for (int i = 0; i < 32; i++){
        if (!(i % 8) && i > 0)
            my_putchar(' ');
        my_putchar((num & left) ? '1' : '0');
        num <<= 1;
    }
}

unsigned int char_nmb_to_int (unsigned char *str, int size)
{
    unsigned int elem = 0;
    int index_str = size - 1;
    for (int i = 0; i < (8 * size); i++) {
        if (!(i % 8) && i > 0)
            index_str--;
        if (str[index_str] & 1)
            elem = modify_bit_n_in_int(elem, i, 1);
        str[index_str] >>= 1;
    }
    return elem;
}
// my_printf("\non concat 4 char en 1 int :\n");
// my_printf("les bits des chars :\n");
// for (int i = 0; i < 4; i++) {
//     print_char_bits(str[i]);
//     my_printf("\n");
// }
// elem |= (1u << 5);  // bit i de elem = 1
// my_printf("les bits du int :\n");
// print_int_bits(elem);
    // for (int c = 0; c < 4; c++) {
    //     if (str[c] & 1)
    //         elem |= (1u << i);  // bit i de elem = 1
    // }
    // elem = (str[i] & 1) ? '1' : '0';
    // param <<= 1;
// }

void life (unsigned char *str, int index)
{
    // my_putchar('\n');
    // for (int i = 0; i < 4; i++) {
    //     print_char_bits(str[index + i]);
    //     my_putchar(' ');
    // }
    int nmb_player = char_nmb_to_int(str + index, 4);
    // print_int_bits(nmb_player);
    my_printf("\nThe player %d(NAME_OF_PLAYER)is alive.\n", nmb_player);
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

int recup_params_according_to_str (unsigned char *str, char *params, int *arr_args, int nmb_funct)
{
    int index = 0, index_arr = 1;
    for (int i = 0; params[i]; i++) {
        my_printf("\non trouve arg %c -> %d\n", params[i], (unsigned int)str[index]);
        my_printf("index : %d\n", index);
        if (params[i] == 'r') {
            arr_args[index_arr++] = (int)str[index];
            index += 1;
        }
        if (params[i] == 'd' && nmb_funct != 10 && nmb_funct != 11) {
            arr_args[index_arr++] = char_nmb_to_int(str + index, 4);    // juste pour index, mettre 4
            index += 4;
        }
        if (params[i] == 'i' || (params[i] == 'd' && (nmb_funct == 10 || nmb_funct == 11))) {
            arr_args[index_arr++] = char_nmb_to_int(str + index, 2);
            index += 2;
        }
    }
    return index;
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

void check_all_functions (unsigned char *str, int size)
{
    int index;
    for (index = 0; str[index] > 0x10 || str[index] < 1 && index < size; index++);
    while (index < size) {
        int nmb_funct = str[index] -  1;
        op_t val = op_tab[nmb_funct];
        my_printf("\nfirst command : `%s` car %d\n", val.mnemonique, str[index]);
        index++;
        if (nmb_funct == 0) {
            life(str, index);
            index += 4;
            my_printf("index %d ? size %d\n", index, size);
            // return;
        } else {
            char *params_types_str = type_param_to_str(str[index]);
            int nmb_args = how_many_args(params_types_str);
            int *args = malloc(sizeof(int) * (nmb_args + 1));
            args[0] = nmb_args;
            char parameter_type = str[index];
            if (!parameter_type)
                return;
            my_printf("on a à la fin `%s` car %d\n", params_types_str, str[index]);
            index++;
            index += recup_params_according_to_str(str + index, params_types_str, args, nmb_funct);
            my_printf("nmb args : %d\n", args[0]);
            for (int index_arr = 1; index_arr <= args[0]; index_arr++) {
                my_printf("arg %d = %d\n", index_arr, args[index_arr]);
            }
            my_printf("END\n");
            free(args);
        }
        // return;
        // struct params_s param;
        // my_printf("parameter type :", val.mnemonique, index);
        // x |= (1u << 3); // 4e bit = 1
        // for (int k = 7; k >= 0; k--) {
        //     // my_printf("%c", (parameter_type & 1) + '0');
        //     types[k] = (parameter_type & 1) + '0';
        //     parameter_type >>= 1;
        //     // if (k == 3)
        //     //     my_putchar(' ');
        // }
        // types[8] = '\0';
        // my_printf("parameter type : %s\n", types);
    }
}

int virtual_machine (char *filepath)
{
    int size = 0, first_command;
    unsigned char *str = filepath_to_str(filepath, &size);
    if (!str)
        return 84;
    disp_str_to_hexa(str, size);
    check_all_functions(str, size);
    my_printf("quit VM\n");
    // char *shorter = str_but_shorter(str, size);
    free(str);
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
