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

// void free_prog (prog_t *prog)
// {
//     free(prog->binaire);
//     free(prog->prog_name);
//     command_s *head = prog->commandes;
//     while (head) {
//         command_s *tmp = head;
//         head = head->next;
//         free(tmp->params);
//         free(tmp->parametres_type);
//         free(tmp);
//     }
//     free(prog);
// }

// void free_alls_progs (prog_t *progs)
// {
//     while (progs) {
//         prog_t *tmp = progs;
//         progs = progs->next;
//         free_prog(tmp);
//     }
// }

void free_my_head (head_cor *cor)
{
    free(cor->mem);
    prog_t *expl = cor->progs;
    while (expl) {
        prog_t *tmp = expl;
        expl = expl->next;
        free(tmp->prog_name);
        free(tmp);
    }
    free(cor);
}
