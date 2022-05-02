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

// register = 1 value

// APC = compteur de programme
// contient ptr vers prochaine execution
// pour savoir où on est / ecrir choses dans la mémoire

// drapeau carry = faux si dernière opération vaut 0


// VM : On envoie executions en param, elle execute

// cycle CYCLE_TO_DIE verif que instruction life est emise ? vie : meurt

// si après NBR_LIVE executions de "live" , process tjrs en vie, CYCLE_TO_DIE -= CYCLE_DELTA unitées
// -> jusqu'a ce qu'in n'y ait plus de process "live"


// registre r1 = numéro des programmes donnés au démarrage


// chaque element s'executes à la fin de son dernier cycle

int ascii_to_hex(char c)
{
    int num = (int) c;
    if (num < 58 && num > 47)
        return num - 48;
    if (num < 103 && num > 96)
        return num - 87;
    return num;
}

// int main()
// {
//         FILE *fp = fopen("sample","r");
//         unsigned char c1,c2;
//         int i = 0;
//         unsigned char sum,final_hex[15/2];
//         for(i = 0; i < 15 / 2; i++)
//         {
//             c1 = ascii_to_hex(fgetc(fp));
//             c2 = ascii_to_hex(fgetc(fp));
//             sum = c1 << 4 | c2;
//             final_hex[i] = sum;
//             printf("%02x ", sum);
//         }
//         printf("\n");
// }

char *char_to_bin_str (char c)
{
    char *str = malloc(sizeof(char) * 9);
    for (int i = 0; i < 8; i++)
        str[i] = (!!((c << i) & 0x80)) + '0';
    str[8] = '\0';
    return str;
}

char *my_scanf (void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t lower_case = 0;
    lower_case = getline(&line, &len, stdin);
    if (lower_case < 0) {
        free(line);
        return NULL;
    }
    return line;
}

int my_base_to_int(char *src, int base)
{
    int result = 0, b = 0;
    int i = my_strlen(src);
    for (i--; i >= 0; i--) {
        result += CTOI(src[i]) * my_compute_power_rec(base, b++);
    }
    return result;
}

int main (int ac, char **av)
{
    if (ac > 1 && !my_strvcmp(av[1], "-h"))
        return help();
    if (ac < 2)
        return 1;
    my_printf("on ouvre %s\n", av[1]);
    char *str = filepath_to_str(av[1]);
    for (int i = 0; i < MEM_SIZE; i++) {
        if (str[i]) {
            char *binary = char_to_bin_str(str[i]);
            char *hexa = my_int_to_base(my_base_to_int(binary, 2), 16);
            my_printf("%s ", hexa);
            free(binary);
            char *base = my_int_to_base(my_abs((int)str[i]), 16);
        }
    }
    // my_putstr("The player NB_OF_PLAYER(NAME_OF_PLAYER)is alive.\n");
    // my_putstr("The player NB_OF_PLAYER(NAME_OF_PLAYER)has won.");
    // my_printf("REG_NUMBER : %d\n", REG_NUMBER);
    // my_printf("REG_SIZE : %d\n", REG_SIZE);
    return 0;
}
