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

int how_many_cycles_for_next (unsigned char *mem, int index)
{
    if (mem[index] <= 0 || (mem[index] - 1) > 0x10) {
        return 0;
    }
    op_t val = op_tab[mem[index] - 1];
    return val.nbr_cycles;
}

prog_t *delete_id_prog_next (prog_t *prog, int id)
{
    prog_t *expl = prog;
    while (expl && expl->next && (id-- - 1))
        expl = expl->next;
    if (!expl->next->next) {
        prog_t *tmp = expl->next;
        expl->next = NULL;
        free(tmp->registres);
        free(tmp);
        return prog;
    }
    prog_t *tmp = expl->next;
    expl->next = expl->next->next;
    free(tmp->registres);
    free(tmp);
    return prog;
}

prog_t *delete_id_prog (prog_t *prog, int id)
{
    prog_t *test_bf = prog;
    if (!prog->next) {
        free(prog->registres);
        free(prog);
        return NULL;
    }
    if (!id) {
        prog_t *tmp = prog;
        prog = prog->next;
        free(tmp->registres);
        free(tmp);
        return prog;
    }
    return delete_id_prog_next(prog, id);
}

int my_strcmp_end (char *str1, char *str2)
{
    int size1 = my_strlen(str1), size2 = my_strlen(str2);
    for (int i1 = size1, i2 = size2; i2 > 0; i1--, i2--) {
        if (i1 <= 0)
            return str2[i2];
        if (str1[i1] != str2[i2])
            return abs(str1[i1] - str2[i2]);
    }
    return 0;
}

int how_many_champs_befor_mem (char **av)
{
    int nmb = 0;
    for (int i = 0; av[i]; i++) {
        if (!my_strcmp_end(av[i], ".cor"))
            nmb++;
    }
    return nmb;
}
