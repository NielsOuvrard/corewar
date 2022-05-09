/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** fichier include de qualité
*/
#pragma once

#ifndef min
# define min(x, y) ({        \
    __typeof__(x) _min1 = (x);        \
    __typeof__(y) _min2 = (y);        \
    (void) (&_min1 == &_min2);        \
    _min1 < _min2 ? _min1 : _min2; })
#endif

#ifndef max
# define max(x, y) ({        \
    __typeof__(x) _max1 = (x);        \
    __typeof__(y) _max2 = (y);        \
    (void) (&_max1 == &_max2);        \
    _max1 > _max2 ? _max1 : _max2; })
#endif

#ifndef abs_diff
# define abs_diff(x, y) ({ \
    __typeof__(x) _a = (x);            \
    __typeof__(y) _b = (y);            \
    (void) (&_a == &_b);            \
    _a > _b ? _a - _b : _b - _a; })
#endif

#ifndef pair
# define pair(x) ({ \
    __typeof__(x) _a = (x);            \
    (_a % 2 == 0) ? 1 : 0; })
#endif

#ifndef my_abs
# define my_abs(x) ({ \
    __typeof__(x) _a = (x);            \
    _a > 0 ? _a : -_a; })
#endif

#define CTOI(x) ((x) - '0')
#define ITOC(x) ((x) + '0')

#define EXIT_ERROR 84
#define EXIT_SUCCESS 0
#define SYNTAX_ERROR_MSG "syntax error"
#define ERROR_MSG  "error"

// * COLOR

#define MY_COLOR_RESET		"\033[0m"
#define MY_COLOR_BOLD		"\033[1m"
#define MY_COLOR_HALFBRIGHT	"\033[2m"
#define MY_COLOR_UNDERSCORE	"\033[4m"
#define MY_COLOR_BLINK		"\033[5m"
#define MY_COLOR_REVERSE	"\033[7m"

/* Standard colors */
#define MY_COLOR_BLACK		"\033[30m"
#define MY_COLOR_RED		"\033[31m"
#define MY_COLOR_GREEN		"\033[32m"
#define MY_COLOR_BROWN		"\033[33m"
#define MY_COLOR_BLUE		"\033[34m"
#define MY_COLOR_MAGENTA	"\033[35m"
#define MY_COLOR_CYAN		"\033[36m"
#define MY_COLOR_GRAY		"\033[37m"

/* Bold variants */
#define MY_COLOR_DARK_GRAY	"\033[1;30m"
#define MY_COLOR_BOLD_RED	"\033[1;31m"
#define MY_COLOR_BOLD_GREEN	"\033[1;32m"
#define MY_COLOR_BOLD_YELLOW	"\033[1;33m"
#define MY_COLOR_BOLD_BLUE	"\033[1;34m"
#define MY_COLOR_BOLD_MAGENTA	"\033[1;35m"
#define MY_COLOR_BOLD_CYAN	"\033[1;36m"

#define MY_COLOR_WHITE		"\033[1;37m"

void free_my_arr (char **arr);

int my_arraylen (char ** world);

int my_compute_power_rec (int nb , int p);

int my_getnbr (char * string);

char *my_int_to_base (int nbr, int base);

char *my_int_to_str(int nb);

int my_intlen (int nbr);

int my_isalpha (char c);

int my_isalphanum (char c);

int my_isdidgit(char a);

int my_isnbr (char *a);

char *my_long_to_base (long nbr, int base);

int my_longlen (long nbr);

char *my_lowercase (char *str);

char *my_memset(char *str, int len, char value);

int my_printf (char * str, ...);

char *my_sprintf (char * str, ...);

int my_put_str_oct (char *str);

void my_putchar(char c);

void my_putfloat (float nombre_decimal);

void my_putint (int nmb);

void my_putlong (long nmb);

void my_putstr (char const *str);

void my_putunsint (unsigned int nmb);

char *my_revstr (char *str);

int my_show_word_array (char * const *tab);

char **str_to_array (char *str);

char *my_strcat(char *dest , char const *src);

int my_strcmp(char const *s1 , char const *s2);

int my_strncmp(char const *s1 , char const *s2, int idx);

int my_strvcmp (char const *str1 , char const *str2);

char *my_strcpy (char *dest, char const *src);

char *my_strdup (char const *src);

int my_strlen(char const *str);

char *my_strupcase(char *str);

int my_unsintlen (unsigned int nbr);

int nbsize(int tmp);

char *nbtstr (int tmp);
