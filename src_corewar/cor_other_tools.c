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

int how_many_args (char *list_args)
{
    int size = 0;
    for (int i = 0; list_args[i]; i++) {
        if (list_args[i] != ' ')
            size++;
    }
    return size;
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
