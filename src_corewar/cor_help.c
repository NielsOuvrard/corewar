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
    my_putstr("    ./corewar [-dump nbr_cycle] [-infos] ");
    my_putstr("[-wait] [[-n prog_number] [-a");
    my_putstr("load_address] prog_name] ...\nDESCRIPTION\n");
    my_putstr("-dump nbr_cycle dumps the memory after the nbr_cycle");
    my_putstr("execution (if the round isn’t\n");
    my_putstr("    already over) with the following");
    my_putstr("format: 64 bytes/line\n");
    my_putstr("    in hexadecimal (A0BCDEFE1DD3...)\n    (100 by default)\n");
    my_putstr("-infos print more informations about commands used\n");
    my_putstr("-wait listen in the stdin enter to pass to the next commande");
    my_putstr("or 'a' to disp the memory\n");
    my_putstr("-n prog_number sets the next program’s number. By default,");
    my_putstr("the first free number in the parameter order\n");
    my_putstr("-a load_address sets the next program’s loading address.");
    my_putstr("When no address is specified, optimize the addresses so that");
    my_putstr("the processes are as far\n");
    my_putstr("    away from each other as possible. The addresses are");
    my_putstr("MEM_SIZE modulo.\n");
    return 0;
}
