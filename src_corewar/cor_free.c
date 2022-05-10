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

void free_my_head (head_cor *cor)
{
    free(cor->mem);
    prog_t *expl = cor->progs;
    while (expl) {
        prog_t *tmp = expl;
        expl = expl->next;
        free(tmp->registres);
        free(tmp->prog_name);
        free(tmp);
    }
    free(cor);
}
