/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int my_strlen (char const *str);

char *my_strcpy (char *dest, char const *src);

char *my_strcat(char *dest, char const *src);

char *my_int_to_str(int nb);

char *str_plus_one(char *str, char c);

char *str_plus_str(char *str, char *str_dos);

char *flag_s_sprint (va_list *list, char *str);

char *flag_c_sprint (va_list *list, char *str);

char *flag_d_sprint (va_list *list, char *str);

char *swich_to_funct_sprint (va_list *list, char *str, char c)
{
    switch (c) {
        case 's':
            return flag_s_sprint(list, str);
        case 'd':
            return flag_d_sprint(list, str);
        case 'i':
            return flag_d_sprint(list, str);
        case 'c':
            return flag_c_sprint(list, str);
        default:
            return str;
    }
    return str;
}

char *my_sprintf (char * str, ... )
{
    va_list list;
    va_start(list, str);
    char *str_returned = malloc(sizeof(char));
    str_returned[0] = '\0';
    for (int a = 0; str[a] != '\0'; a++) {
        if (str[a] == '%' && str[a + 1] != '\0'
        && str[a + 1] != '%') {
            str_returned = swich_to_funct_sprint(&list,
            str_returned, str[++a]);
        } else if (str[a] == '%' && str[a + 1] != '\0' &&
        str[a + 1] == '%') {
            str_returned = str_plus_one(str_returned, '%');
            a++;
        } else {
            str_returned = str_plus_one(str_returned, str[a]);
        }
    }
    va_end(list);
    return str_returned;
}
