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

int modify_bit_n_in_int (int nmb, int where, bool bit)
{
    if (bit)
        return nmb | (1u << where);
    return nmb ^ (1u << where);
}

void print_char_bits (unsigned char c)
{
    unsigned char left = 1 << 7;
    for (char i = 0; i < 8; i++){
        my_putchar((c & left) ? '1' : '0');
        c <<= 1;
    }
}

void print_int_bits (unsigned int num)
{
    unsigned int left = 1 << 31;
    for (int i = 0; i < 32; i++){
        if (!(i % 8) && i > 0)
            my_putchar(' ');
        my_putchar((num & left) ? '1' : '0');
        num <<= 1;
    }
}

unsigned int char_nmb_to_int (unsigned char *str, int size)
{
    unsigned int elem = 0;
    int index_str = size - 1;
    for (int i = 0; i < (8 * size); i++) {
        if (!(i % 8) && i > 0)
            index_str--;
        if (str[index_str] & 1)
            elem = modify_bit_n_in_int(elem, i, 1);
        str[index_str] >>= 1;
    }
    return elem;
}
