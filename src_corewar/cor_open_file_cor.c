/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** pour open file cor
*/

#include "op.h"
#include "my.h"
#include "cor_header.h"

char *char_to_bin_str (char c)
{
    char *str = malloc(sizeof(char) * 9);
    for (int i = 0; i < 8; i++)
        str[i] = (!!((c << i) & 0x80)) + '0';
    str[8] = '\0';
    return str;
}

int my_base_to_int(char *src, int base)
{
    int result = 0, b = 0, i = my_strlen(src);
    for (i--; i >= 0; i--)
        result += CTOI(src[i]) * my_compute_power_rec(base, b++);
    return result;
}

char **copy_array_plus_one (char **src, char *one)
{
    int size = my_arraylen(src), i;
    char **dest = malloc(sizeof(char *) * (size + 2));
    if (dest == NULL)
        return NULL;
    for (i = 0; src[i] != NULL; i++)
        dest[i] = src[i];
    dest[i] = one;
    dest[i + 1] = NULL;
    free(src);
    return dest;
}

char **file_cor_to_array(char *filepath)
{
    int size = 0;
    unsigned char *str = filepath_to_str(filepath, &size);
    if (!str)
        return NULL;
    char **array = malloc(sizeof(char *));
    array[0] = NULL;
    for (int i = 0; i < size; i++) {
        if (str[i]) {
            char *binary = char_to_bin_str(str[i]);
            char *hexa = my_int_to_base(my_base_to_int(binary, 2), 16);
            free(binary);
            array = copy_array_plus_one(array, hexa);
        }
    }
    return array;
}

void disp_str_to_hexa (unsigned char *str, int size)
{
    if (!str)
        return;
    int b = 0;
    int time_force_print = 0;
    for (int i = 0; i < size - 1; i++) {
        if (str[i] || time_force_print) {
            if (str[i]) {
                char *binary = char_to_bin_str(str[i]);
                char *hexa = my_int_to_base(my_base_to_int(binary, 2), 16);
                my_putstr(hexa);
                my_putchar('\t');
                free(binary);
                free(hexa);
                time_force_print = 10;
            } else {
                my_putstr("0\t");
                time_force_print--;
            }
            b++;
            if (!(b % 10))
                my_putchar('\n');
        }
    }
}
