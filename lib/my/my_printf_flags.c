/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdarg.h>
#include <stdlib.h>
#include "my.h"

int flag_s (va_list *list)
{
    char *temp = va_arg(*list, char *);
    if (!temp) {
        my_putstr("(null)");
        return 1;
    }
    my_putstr(temp);
    return 0;
}

int flag_c (va_list *list)
{
    char temp = va_arg(*list, int);
    my_putchar(temp);
    return 0;
}

int flag_d (va_list *list)
{
    int temp = va_arg(*list, int);
    my_putint(temp);
    return 0;
}

int flag_x (va_list *list)
{
    char *temp = my_int_to_base(va_arg(*list, int), 16);
    my_putstr(temp);
    free(temp);
    return 0;
}

