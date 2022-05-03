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

// struct params_s {
// 	unsigned a : 2;
// 	unsigned b : 2;
// 	unsigned c : 2;
// 	unsigned d : 2;
// };

void life (void)
{
    
}

void check_all_functions (char *str, int size)
{
    int index;
    for (index = 0; str[index] > 0x10 || str[index] < 1 && index < size; index++);
    for (index; index < size; index++) {
        int nmb_funct = str[index] -  1;
        op_t val = op_tab[nmb_funct];
        my_printf("\nfirst command : %s\n en %d\n", val.mnemonique, index);
        char parameter_type = str[++index];
        if (!parameter_type)
            return;
        if (nmb_funct == 1)
            life();
        // struct params_s param;
        // // my_printf("parameter type :", val.mnemonique, index);
        // char types[9];
        // unsigned left_bit = 0x80;
        // for (int k = 0; k < 8; k++) {
        //     types[k] = (parameter_type & left_bit) ? '1' : '0';
        //     parameter_type <<= 1;
        // }


        // x |= (1u << 3); // 4e bit = 1

        // for (int k = 7; k >= 0; k--) {
        //     // my_printf("%c", (parameter_type & 1) + '0');
        //     types[k] = (parameter_type & 1) + '0';
        //     parameter_type >>= 1;
        //     // if (k == 3)
        //     //     my_putchar(' ');
        // }
        // types[8] = '\0';
        // my_printf("parameter type : %s\n", types);
        return;
    }
}

int virtual_machine (char *filepath)
{
    int size = 0, first_command;
    char *str = filepath_to_str(filepath, &size);
    if (!str)
        return 84;
    disp_str_to_hexa(str, size);
    check_all_functions(str, size);
    // char *shorter = str_but_shorter(str, size);
    free(str);
    // my_putstr("\nen hexa :\n");
    // disp_str_to_hexa(shorter, my_strlen(shorter));
    // for (first_command = 0; shorter[first_command] > 0x10 || shorter[first_command] < 1; first_command++);
    // op_t val = op_tab[shorter[first_command] -  1];
    // my_printf("\nfirst command : %s\n en %d\n", val.mnemonique, first_command);
    // find_commandes(shorter);
    // for (int i = 0; shorter[i]; i++) {
    //     char zero = shorter[i];
    //     for (int k = 0; k < 8; k++) {
    //         my_printf("%c", (zero & 1) + '0');
    //         zero >>= 1;
    //         if (k == 3)
    //             my_putchar(' ');
    //     }
    //     my_printf("\n");
    // }
    // free(shorter);
    return 0;
}
