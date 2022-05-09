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

int start_cycles (prog_t *prog)
{
    prog_t *expl = prog;
    for (int cycle = 0; cycle < 10; cycle++) {
        while (expl) {
            op_t val = op_tab[expl->commandes->function];
            if (cycle >= val.nbr_cycles) {
            }
            // op_t val = op_tab[com->function];
            // my_printf("com %s\nargs : ", val.mnemonique);
            // for (int a = 1; a < com->params[0] + 1; a++)
            //     my_printf("'%d' ", com->params[a]);
            // my_printf("\ncycles : %d\n\n", val.nbr_cycles);
            expl = expl->next;
        }
    }
    return 0;
}
