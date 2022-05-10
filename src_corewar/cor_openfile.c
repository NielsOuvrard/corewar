/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** pour open file
*/

#include "op.h"
#include "my.h"
#include "cor_header.h"

unsigned char *filepath_to_str (char *filepath, int *size_str)
{
    int buff_size = MEM_SIZE, len = 0;
    unsigned char *buff = malloc(sizeof(char) * buff_size);
    int fp = open(filepath, O_RDONLY);
    if (!fp)
        return NULL;
    while ((len = read(fp, buff + (*size_str), buff_size - (*size_str))) > 0)
        (*size_str) += len;
    close(fp);
    if (len < 0)
        return NULL;
    return buff;
}

char *str_plus_one (char *src, char c)
{
    int size = my_strlen(src);
    char *dest = malloc(sizeof(char) * (size + 2));
    my_strcpy(dest, src);
    dest[size] = c;
    dest[size + 1] = '\0';
    free(src);
    return dest;
}
