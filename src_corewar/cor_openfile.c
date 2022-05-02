/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** pour open file
*/

#include "op.h"
#include "my.h"
#include "cor_header.h"

char *filepath_to_str (char *filepath)
{
    int buff_size = MEM_SIZE, offset = 0, len = 0;
    char *buff = malloc(sizeof(char) * buff_size);
    int fp = open(filepath, O_RDONLY);
    if (!fp)
        return NULL;
    while ((len = read(fp, buff + offset, buff_size - offset)) > 0)
        offset += len;
    close(fp);
    if (len < 0)
        return NULL;
    return buff;
}

char **filepath_to_arr (char *filepath)
{
    char *buff = filepath_to_str(filepath);
    if (!buff)
        return NULL;
    int offset, a = 0, k, i, j = 0;
    offset = my_strlen(buff);
    for (int kfc = 0; buff[kfc] != '\0'; kfc++)
        if (buff[kfc] == '\n')
            a++;
    char **map = malloc(sizeof(char *) * (a + 2));
    for (i = 0; a > i; i++) {
        map[i] = malloc(sizeof(char) * (offset));
        for (k = 0; buff[j] != '\n'; k++)
            map[i][k] = buff[j++];
        j++;
        map[i][k] = '\0';
    }
    map[a] = NULL;
    free(buff);
    return map;
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

char *str_but_shorter (char *src)
{
    char *str = malloc(sizeof(char));
    str[0] = '\0';
    for (int i = 0; i < MEM_SIZE; i++)
        if (src[i])
            str = str_plus_one(str, src[i]);
    return str;
}
