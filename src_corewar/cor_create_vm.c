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

// for copy reg ?

prog_t *add_prog (prog_t *dest, prog_t *new)
{
    prog_t *begin = dest;
    new->next = NULL;
    if (!begin) {
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
    cor->cycle_to_die_init = CYCLE_TO_DIE;
    cor->nmb_live_cycle = NBR_LIVE;
    cor->recurence_dump = 100;
    cor->champions_id = NULL;
    return cor;
}

void my_strvcpy (unsigned char *dest, unsigned char *src,
int size, int idx_dest)
{
    for (int i = 0; i < size; i++)
        dest[idx_dest + i] = src[i];
}

prog_t *open_a_binary (char *filepath)
{
    prog_t *programme = malloc(sizeof(prog_t));
    programme->prog_name = NULL;
    return programme;
}

int exist_in_list (chmp_id *list, int id)
{
    while (list) {
        if (list->id == id)
            return 1;
        list = list->next;
    }
    return 0;
}

chmp_id *new_chmp (chmp_id *list, int id)
{
    chmp_id *new = malloc(sizeof(chmp_id));
    new->id = id;
    new->next = NULL;
    if (!list)
        return new;
    new->next = list;
    return new;
}

bool binary_to_mem (int nmb_chmp, load_champ parametres, head_cor *cor, int idx)
{
    prog_t *prog = open_a_binary(parametres.filepath);
    if (!prog)
        return 0;
    prog->registres = malloc(sizeof(int) * REG_NUMBER);
    for (int i = 1; i < REG_NUMBER; i++)
        prog->registres[i] = 0;
    if (parametres.n && !exist_in_list(cor->champions_id, parametres.prog_nmb)) {
        prog->registres[0] = parametres.prog_nmb;
    } else {
        while (exist_in_list(cor->champions_id, cor->nmb_player))
            cor->nmb_player++;
        prog->registres[0] = cor->nmb_player;
    }
    cor->champions_id = new_chmp(cor->champions_id, prog->registres[0]);
    cor->progs = add_prog(cor->progs, prog);
    int size = 0, decale = COMMENT_LENGTH;
    unsigned char *str = filepath_to_str(parametres.filepath, &size);
    if (!str || !check_magic(str, size, &prog->prog_name))
        return 0;
    prog->pc = idx * (MEM_SIZE / nmb_chmp);
    my_printf("chmp en %d car idx = %d\n", prog->pc, idx);
    if (parametres.a)
        prog->pc = parametres.load_adress;
    for (; str[decale] > 0x10 || str[decale] < 1 && decale < size; decale++);
    my_strvcpy(cor->mem, str + decale, size - decale, prog->pc);
    free(str);
    for (int i = 0; i < size - decale; i++)
        cor->who[prog->pc + i] = prog->registres[0];
    op_t val = op_tab[cor->mem[prog->pc] - 1];
    prog->cycle_to_wait = val.nbr_cycles;
    prog->carry = 1;
    prog->cycle_to_die = CYCLE_TO_DIE;
    return 1;
}
