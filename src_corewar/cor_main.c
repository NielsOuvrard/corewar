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

int nmb_processus (prog_t *prog)
{
    int a = 1;
    prog_t *cmp = prog;
    prog = prog->next;
    while (prog) {
        if (prog->registres[0] != cmp->registres[0])
            a++;
        prog = prog->next;
    }
    return a;
}

// char *str = my_scanf();
// if (!str) {
//     // free_my_head(cor);
//     return 0;
// } else if (str[0] == 'a') {
//     dump_all(cor);
// }
// free(str);
int open_programs (int ac, char **av)
{
    head_cor *cor = complete_with_args(ac, av);
    if (!cor)
        return 84;
    dump_all(cor);
    for (int cycle = 0;; cycle++) {
        begin_virtual_machine(cor);
        if (cor->dump && !(cycle % cor->recurence_dump)) {
            dump_all(cor);
        }
        if (nmb_processus(cor->progs) == 1) {
            dump_all(cor);
            my_printf("The player %d (%s) has won.\n\n",
            cor->progs->registres[0], cor->progs->prog_name);
            free_my_head(cor);
            return 0;
        }
    }
    return 0;
}

int main (int ac, char **av)
{
    if (ac > 1 && !my_strvcmp(av[1], "-h"))
        return help();
    if (ac < 2)
        return 1;
    return open_programs(ac, av);
}
