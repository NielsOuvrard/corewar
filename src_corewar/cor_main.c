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

// char **file = file_cor_to_array(av[1], size);
// if (!file)
//     return 84;
// my_printf("\nle array :\n");
// for (int i = 0; file[i]; i++) {
//     if (!(i % 10))
//         my_putchar('\n');
//     my_printf("%s\t", file[i]);
// }
// free_my_arr(file);

int main (int ac, char **av)
{
    if (ac > 1 && !my_strvcmp(av[1], "-h"))
        return help();
    if (ac < 2)
        return 1;
    if (virtual_machine(av[1]) == 84)
        return 84;
    my_putstr("\n\nThe player NB_OF_PLAYER(NAME_OF_PLAYER)is alive.\n");
    // my_putstr("The player NB_OF_PLAYER(NAME_OF_PLAYER)has won.");
    // my_printf("REG_NUMBER : %d\n", REG_NUMBER);
    // my_printf("REG_SIZE : %d\n", REG_SIZE);
    return 0;
}
