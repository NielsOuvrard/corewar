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

prog_t *add_prog (prog_t *dest, prog_t *new)
{
    prog_t *begin = dest;
    if (!begin) {
        new->next = NULL;
        return new;
    }
    while (dest && dest->next)
        dest = dest->next;
    dest->next = new;
    return begin;
}

head_cor *create_mem (void)
{
    head_cor *cor = malloc(sizeof(head_cor));
    cor->mem = malloc(sizeof(unsigned char) * MEM_SIZE);
    for (int i = 0; i < MEM_SIZE; i++)
        cor->mem[i] = '\0';
    cor->who = malloc(sizeof(char) * MEM_SIZE);
    for (int i = 0; i < MEM_SIZE; i++)
        cor->who[i] = '\0';
    cor->progs = NULL;
    cor->nmb_player = 1;
    // cor->cycle_delta = CYCLE_DELTA;
    cor->cycle_to_die_init = CYCLE_TO_DIE;
    cor->recurence_dump = 100;
    return cor;
}

void my_strvcpy (unsigned char *dest, unsigned char *src,
int size, int idx_dest)
{
    for (int i = 0; i < size; i++)
        dest[idx_dest + i] = src[i];
}

bool binary_to_mem (int ac, char *filepath, head_cor *cor, int idx)
{
    prog_t *prog = open_a_binary(filepath);
    if (!prog)
        return 0;
    prog->nmb_player = cor->nmb_player++;
    prog->registres = malloc(sizeof(int) * REG_NUMBER);
    for (int i = 0; i < REG_NUMBER; i++)
        prog->registres[i] = 0;
    cor->progs = add_prog(cor->progs, prog);
    int size = 0, decale = COMMENT_LENGTH;
    unsigned char *str = filepath_to_str(filepath, &size);
    if (!str || !check_magic(str, size, &prog->prog_name))
        return 0;
    prog->registres[0] = idx * (MEM_SIZE / (ac - 1));
    for (; str[decale] > 0x10 || str[decale] < 1 && decale < size; decale++);
    my_strvcpy(cor->mem, str + decale, size - decale, prog->registres[0]);
    free(str);
    for (int i = 0; i < size - decale; i++)
        cor->who[prog->registres[0] + i] = prog->nmb_player;
    op_t val = op_tab[cor->mem[prog->registres[0]] - 1];
    prog->cycle_to_wait = val.nbr_cycles;
    prog->carry = 1;
    prog->cycle_to_die = CYCLE_TO_DIE;
    return 1;
}
