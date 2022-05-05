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

typedef struct command_s {
    int function;
    char *parametres_type;
    int *params;
    int size_cycle;
    struct command_s *next;
} command_s;

typedef struct prog_t {
    char *prog_name;
    unsigned char *binaire;
    int size_binaire;
    int index;
    // int fun_actual;
    command_s *commandes;
} prog_t;

// help

int help (void);

// openfile

unsigned char *filepath_to_str (char *filepath, int *size_str);

char *str_but_shorter (char *src, int size);

// open file cor

char **file_cor_to_array(char *filepath);

void disp_str_to_hexa (unsigned char *str, int size);

// tools bit

int modify_bit_n_in_int (int nmb, int where, bool bit);

void print_char_bits (unsigned char c);

void print_int_bits (unsigned int num);

unsigned int char_nmb_to_int (unsigned char *str, int size);


// virtual machine

int virtual_machine (char *filepath);

// op.c

void find_commandes (char *str);
