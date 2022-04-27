/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** thr_good_corewar
*/

#include "cor_header.h"
#include "my.h"
#include "op.h"

int main (int ac, char **av)
{
    char *str = my_sprintf("le %s %c %d %s.", "chat", 'a', 47, "dents");
    my_putstr(str);
    free(str);
    return 0;
}
