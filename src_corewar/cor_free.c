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

void free_prog (prog_t *prog)
{
    free(prog->binaire);
    free(prog->prog_name);
    command_s *head = prog->commandes;
    while (head) {
        command_s *tmp = head;
        head = head->next;
        free(tmp->params);
        free(tmp);
    }
    free(prog);
}
