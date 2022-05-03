/*
** EPITECH PROJECT, 2022
** help
** File description:
** corwar
*/

#include "my.h"

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
