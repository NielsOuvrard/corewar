/*
** EPITECH PROJECT, 2021
** header du my tet
** File description:
** bcp de definitions
*/

#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <getopt.h>

// openfile

char *filepath_to_str (char *filepath);

char *str_but_shorter (char *src);

// open file cor

char **file_cor_to_array(char *filepath);

void disp_str_to_hexa (char *str);
