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

char *str_plus_one(char *str, char c)
{
    int size = my_strlen(str);
    char *new = malloc(sizeof(char) * (size + 2));
    my_strcpy(new, str);
    free(str);
    new[size] = c;
    new[size + 1] = '\0';
    return new;
}

char *str_plus_str(char *str, char *str_dos)
{
    int size = my_strlen(str) + my_strlen(str_dos);
    char *new = malloc(sizeof(char) * (size + 2));
    my_strcpy(new, str);
    my_strcat(new, str_dos);
    free(str);
    new[size + 1] = '\0';
    return new;
}

char *flag_s_sprint (va_list *list, char *str)
{
    char *temp = va_arg(*list, char *);
    if (!temp)
        return str_plus_str(str, "(null)");
    return str_plus_str(str, temp);
}

char *flag_c_sprint (va_list *list, char *str)
{
    char temp = va_arg(*list, int);
    return str_plus_one(str, temp);
}

char *flag_d_sprint (va_list *list, char *str)
{
    int temp = va_arg(*list, int);
    char *val = my_int_to_str(temp);
    str = str_plus_str(str, val);
    if (temp)
        free(val);
    return str;
}
