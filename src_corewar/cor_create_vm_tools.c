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

prog_t *add_prog (prog_t *dest, prog_t *new)
{
    prog_t *begin = dest;
    new->next = NULL;
    if (!begin) {
        return new;
    }
    while (dest && dest->next)
        dest = dest->next;
    dest->next = new;
    return begin;
}


void my_strvcpy (unsigned char *dest, unsigned char *src,
int size, int idx_dest)
{
    for (int i = 0; i < size; i++)
        dest[idx_dest + i] = src[i];
}

prog_t *open_a_binary (char *filepath)
{
    prog_t *programme = malloc(sizeof(prog_t));
    programme->prog_name = NULL;
    return programme;
}

int exist_in_list (chmp_id *list, int id)
{
    while (list) {
        if (list->id == id)
            return 1;
        list = list->next;
    }
    return 0;
}

chmp_id *new_chmp (chmp_id *list, int id)
{
    chmp_id *new = malloc(sizeof(chmp_id));
    new->id = id;
    new->next = NULL;
    if (!list)
        return new;
    new->next = list;
    return new;
}
