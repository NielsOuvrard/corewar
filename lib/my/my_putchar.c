/*
** EPITECH PROJECT, 2021
** task02
** File description:
** description du fichier
*/

#include <unistd.h>

void my_putchar (char c)
{
    write(1, &c, 1);
}
