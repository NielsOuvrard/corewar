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

int how_many_champs_befor_mem (char **av);

load_champ the_for_of_complete_with_args (char **av, int *i)
{
    load_champ parametres;
    parametres.a = 0;
    parametres.n = 0;
    if (!my_strcmp(av[(*i)], "-n") && av[(*i) + 1] &&
    my_isnbr(av[++(*i)]) && av[(*i) + 1]) {
        parametres.n = 1;
        parametres.prog_nmb = my_getnbr(av[(*i)++]);
    }
    if (!my_strcmp(av[(*i)], "-a") && av[(*i) + 1] &&
    my_isnbr(av[++(*i)]) && av[(*i) + 1]) {
        parametres.a = 1;
        parametres.load_adress = my_getnbr(av[(*i)++]);
    }
    parametres.filepath = av[(*i)];
    return parametres;
}

head_cor *complete_with_args (int ac, char **av)
{
    head_cor *cor = create_mem();
    int start = 1;
    if (!my_strcmp(av[start], "-dump") && av[2] && my_isnbr(av[2]))
        my_printf("", start += 2, cor->dump = 1,
        cor->recurence_dump = my_getnbr(av[2]));
    if (!my_strcmp(av[start], "-infos"))
        my_printf("", start++, cor->more_infos = 1);
    if (!my_strcmp(av[start], "-wait"))
        my_printf("", start++, cor->wait = 1);
    int nmb_cham = how_many_champs_befor_mem(av);
    int idx_align_com = 0;
    for (int i = start; i < ac; i++) {
        load_champ parametres = the_for_of_complete_with_args(av, &i);
        if (!binary_to_mem(nmb_cham, parametres, cor, idx_align_com++)) {
            free(cor->mem);
            free(cor);
            return NULL;
        }
    }
    return cor;
}
