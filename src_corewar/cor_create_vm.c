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

prog_t *add_prog (prog_t *dest, prog_t *new);

void my_strvcpy (unsigned char *dest, unsigned char *src,
int size, int idx_dest);

prog_t *open_a_binary (char *filepath);

int exist_in_list (chmp_id *list, int id);

chmp_id *new_chmp (chmp_id *list, int id);

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
    cor->more_infos = 0;
    cor->dump = 0;
    cor->wait = 0;
    return cor;
}

void binary_to_mem_next (head_cor *cor, prog_t *prog, load_champ parametres)
{
    prog->registres = malloc(sizeof(int) * REG_NUMBER);
    for (int i = 1; i < REG_NUMBER; i++)
        prog->registres[i] = 0;
    if (parametres.n && !exist_in_list(cor->champions_id,
    parametres.prog_nmb)) {
        prog->registres[0] = parametres.prog_nmb;
    } else {
        while (exist_in_list(cor->champions_id, cor->nmb_player))
            cor->nmb_player++;
        prog->registres[0] = cor->nmb_player;
    }
    cor->champions_id = new_chmp(cor->champions_id, prog->registres[0]);
    cor->progs = add_prog(cor->progs, prog);
}

bool binary_to_mem (int nmb_chmp, load_champ parametres, head_cor *cor,
int idx)
{
    prog_t *prog = open_a_binary(parametres.filepath);
    if (!prog)
        return 0;
    binary_to_mem_next(cor, prog, parametres);
    int size = 0, decale = COMMENT_LENGTH;
    unsigned char *str = filepath_to_str(parametres.filepath, &size);
    if (!str || !check_magic(str, size, &prog->prog_name))
        return 0;
    prog->pc = idx * (MEM_SIZE / nmb_chmp);
    if (parametres.a)
        prog->pc = parametres.load_adress;
    for (; str[decale] > 0x10 || str[decale] < 1 && decale < size; decale++);
    my_strvcpy(cor->mem, str + decale, size - decale, prog->pc);
    free(str);
    for (int i = 0; i < size - decale; i++)
        cor->who[prog->pc + i] = prog->registres[0];
    op_t val = op_tab[cor->mem[prog->pc] - 1];
    prog->cycle_to_wait = val.nbr_cycles;
    my_printf("", prog->carry = 1, prog->cycle_to_die = CYCLE_TO_DIE);
    return 1;
}
