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

// void disp_str_to_hexa (unsigned char *str, char *who, int size)
// {
//     if (!str)
//         return;
//     int b = 0;
//     int time_force_print = 1;
//     for (int i = 0; i < size; i++) {
//         my_printf("\033[%dm", 97 - who[i]);
//         // my_printf("\033[%dm", 107 - who[i]);
//         char *binary = char_to_bin_str(str[i]);
//         char *hexa;
//         hexa = my_int_to_base(my_base_to_int(binary, 2), 16);
//         if (my_strlen(hexa) < 2)
//             my_putchar('0');
//         if (my_strlen(hexa) < 1)
//             my_putchar('0');
//         my_putstr(hexa);
//         my_putchar(' ');
//         free(binary);
//         free(hexa);
//         my_putstr(MY_COLOR_RESET);
//         if (++b == 64)
//             my_printf("\n", "\n%d\n", i, b = 0);
//     }
// }

char *char_to_hexa (char c)
{
    char *str = malloc(sizeof(char) * 3);
    char caract[] = "0123456789abcdef";
    int incr = 8, index = 0, decale = 7, idx_str = 0;
    for (int i = 0; i < 8; i++) {
        if (i == 4) {
            str[idx_str++] = caract[index];
            incr = 8, index = 0;
        }
        if ((c >> decale) & 1)
            index += incr;
        incr /= 2;
        decale--;
    }
    str[idx_str++] = caract[index];
    str[idx_str] = '\0';
    return str;
}

void print_to_hexa (char c)
{
    char caract[] = "0123456789abcdef";
    int incr = 8, index = 0, decale = 7;
    for (int i = 0; i < 8; i++) {
        if (i == 4) {
            my_putchar(caract[index]);
            incr = 8, index = 0;
        }
        if ((c >> decale) & 1)
            index += incr;
        incr /= 2;
        decale--;
    }
    my_putchar(caract[index]);
}

void dump_all (head_cor *cor)
{
    int b = 0;
    for (int i = 0; i < MEM_SIZE; i++) {
        my_printf("\033[%dm", 97 - cor->who[i]);
        prog_t *expl = cor->progs;
        while (expl) {
            if (expl->registres[0] == i)
                my_printf("%s\033[%dm", MY_COLOR_RESET, 107 - cor->who[i]);
            expl = expl->next;
        }
        print_to_hexa(cor->mem[i]);
        my_putstr(MY_COLOR_RESET);
        my_putchar(' ');
        if (++b == 64)
            my_printf("\n", b = 0);
    }
    prog_t *expl = cor->progs;
    while (expl) {
        my_printf("\033[%dmProg %d -> registeres :\n", 97 - expl->nmb_player, expl->nmb_player);
        for (int i = 0; i < REG_NUMBER; i++) {
            my_printf("r%d\t", i + 1);
            print_int_bits(expl->registres[i]);
            my_printf("\t->\t%d\n", expl->registres[i]);
        }
        my_printf("\ncycle_to_die : %d\n", expl->cycle_to_die);
        expl = expl->next;
    }
    my_putstr(MY_COLOR_RESET);
}
