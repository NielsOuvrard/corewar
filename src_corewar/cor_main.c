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

int help (void)
{
    my_putstr("USAGE\n");
    my_putstr("./corewar [-dump nbr_cycle] [[-n prog_number] [-a \
load_address] prog_name] ...\nDESCRIPTION\n");
    my_putstr("-dump nbr_cycle dumps the memory after the nbr_cycle \
execution (if the round isn’t\nalready over) with the following \
format: 32 bytes/line\n");
    my_putstr("in hexadecimal (A0BCDEFE1DD3...)\n");
    my_putstr("-n prog_number sets the next program’s number. By default, \
the first free number in the parameter order\n");
    my_putstr("-a load_address sets the next program’s loading address. \
When no address is specified, optimize the addresses so that \
the processes are as far\n");
    my_putstr("away from each other as possible. The addresses are \
MEM_SIZE modulo.\n");
    return 0;
}

int main (int ac, char **av)
{
    if (ac > 1 && !my_strvcmp(av[1], "-h"))
        return help();
    if (ac < 2)
        return 1;
    char *str = filepath_to_str(av[1]);
    char *shorter = str_but_shorter(str);
    free(str);
    for (int i = 0; shorter[i]; i++)
        my_printf("%d\t", shorter[i]);
    // my_putstr(shorter);
    my_putstr("\n\n");
    disp_str_to_hexa(shorter);

    // char **file = file_cor_to_array(av[1]);
    // if (!file)
    //     return 84;
    // my_printf("\nle array :\n");
    // for (int i = 0; file[i]; i++) {
    //     if (!(i % 10))
    //         my_putchar('\n');
    //     my_printf("%s\t", file[i]);
    // }
    // free_my_arr(file);
    my_putstr("\n\nThe player NB_OF_PLAYER(NAME_OF_PLAYER)is alive.\n");
    // my_putstr("The player NB_OF_PLAYER(NAME_OF_PLAYER)has won.");
    // my_printf("REG_NUMBER : %d\n", REG_NUMBER);
    // my_printf("REG_SIZE : %d\n", REG_SIZE);
    return 0;
}
