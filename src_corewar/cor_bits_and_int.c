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

// brk
// sbrk

// strace

// struct a {
//     unsigned var : 7;
//     unsigned vari : 32;
//     int vari;
// };

char last_octet_int_to_char (int a)
{
    char c = 0;
    for (int i = 0; i < 8; i++)
        c |= (a & (1 << i));
    return c;
}

void modify_str_with_bits (unsigned char *str, int bits)
{
    str[3] = last_octet_int_to_char(bits);
    str[2] = last_octet_int_to_char(bits >>= 8);
    str[1] = last_octet_int_to_char(bits >>= 8);
    str[0] = last_octet_int_to_char(bits >>= 8);
}
