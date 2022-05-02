/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdarg.h>
#include "my.h"

int flag_s (va_list *list);

int flag_c (va_list *list);

int flag_d (va_list *list);

int flag_x (va_list *list);

int swich_to_funct (va_list *list, char c)
{
    switch (c) {
        case 's':
            return flag_s(list);
        case 'd':
            return flag_d(list);
        case 'i':
            return flag_d(list);
        case 'c':
            return flag_c(list);
        case 'x':
            return flag_x(list);
        default:
            return 0;
    }
    return 0;
}

int my_printf (char * str, ... )
{
    int return_value = 0;
    va_list list;
    va_start(list, str);
    for (int a = 0; str[a] != '\0'; a++) {
        if (str[a] == '%' && str[a + 1] != '\0' && str[a + 1] != '%') {
            return_value += swich_to_funct(&list, str[++a]);
        } else if (str[a] == '%' && str[a + 1] != '\0' && str[a + 1] == '%') {
            my_putchar('%');
            a++;
        } else {
            my_putchar(str[a]);
        }
    }
    va_end(list);
    return return_value;
}
