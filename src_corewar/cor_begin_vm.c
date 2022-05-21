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

prog_t *in_the_for_of_vm (head_cor *cor, prog_t *expl, int id, int *stop)
{
    if (expl->cycle_to_wait > 0) {
        expl->cycle_to_wait--;
    } else {
        (*stop) = 1;
        execute_this_commande(cor, expl);
        expl->cycle_to_wait = how_many_cycles_for_next(cor->mem, expl->pc);
    }
    if (0 > (expl->cycle_to_die--)) {
        dump_all(cor);
        cor->progs = delete_id_prog(cor->progs, id);
        expl = cor->progs;
        for (int i = 0; i < id - 1; i++)
            expl = expl->next;
    }
    return expl;
}

void begin_virtual_machine (head_cor *cor)
{
    prog_t *expl = cor->progs;
    int stop = 0;
    for (int id = 0; expl; id++) {
        expl = in_the_for_of_vm(cor, expl, id, &stop);
        if (expl)
            expl = expl->next;
    }
    if (!stop)
        return;
    if (cor->wait) {
        char *str = my_scanf();
        if (!str)
            return;
        else if (str[0] == 'a')
            dump_all(cor);
        free(str);
    }
}
