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
    int size_cycle;
    int next_fun;
    int *params;
    char *parametres_type;
} command_s;

typedef struct prog_t {
    bool carry;
    // int nmb_player;
    int pc;
    int cycle_to_die;
    int cycle_to_wait;
    int *registres;
    char *prog_name;
    struct prog_t *next;
} prog_t;

typedef struct chmp_id {
    int id;
    struct chmp_id *next;
} chmp_id;

typedef struct head_cor {
    int nmb_player;
    int cycle_to_die_init;
    int nmb_live_cycle;
    int recurence_dump;
    char *who;
    unsigned char *mem;
    prog_t *progs;
    chmp_id *champions_id;
} head_cor;

typedef struct load_champ {
    bool n;
    int prog_nmb;
    bool a;
    int load_adress;
    char *filepath;
} load_champ;

// commandes

int fun_live    (head_cor *cor, prog_t *prog, command_s *com);
int fun_ld      (head_cor *cor, prog_t *prog, command_s *com);
int fun_st      (head_cor *cor, prog_t *prog, command_s *com);
int fun_add     (head_cor *cor, prog_t *prog, command_s *com);
int fun_sub     (head_cor *cor, prog_t *prog, command_s *com);
int fun_and     (head_cor *cor, prog_t *prog, command_s *com);
int fun_or      (head_cor *cor, prog_t *prog, command_s *com);
int fun_xor     (head_cor *cor, prog_t *prog, command_s *com);
int fun_zjmp    (head_cor *cor, prog_t *prog, command_s *com);
int fun_ldi     (head_cor *cor, prog_t *prog, command_s *com);
int fun_sti     (head_cor *cor, prog_t *prog, command_s *com);
int fun_fork    (head_cor *cor, prog_t *prog, command_s *com);
int fun_lld     (head_cor *cor, prog_t *prog, command_s *com);
int fun_lldi    (head_cor *cor, prog_t *prog, command_s *com);
int fun_lfork   (head_cor *cor, prog_t *prog, command_s *com);
int fun_aff     (head_cor *cor, prog_t *prog, command_s *com);

// arguments input

int how_many_cycles_for_next (unsigned char *mem, int index);

prog_t *delete_id_prog (prog_t *prog, int id);

void begin_virtual_machine (head_cor *cor);

head_cor *complete_with_args (int ac, char **av);

// create VM

prog_t *add_prog (prog_t *dest, prog_t *new);

head_cor *create_mem (void);

void my_strvcpy (unsigned char *dest, unsigned char *src,
int size, int idx_dest);

bool binary_to_mem (int ac, load_champ parametres, head_cor *cor, int idx);

// dump all

void dump_all (head_cor *cor);

void print_to_hexa (char c);

// cycles

int start_cycles (prog_t *prog);

// free

void free_my_head (head_cor *cor);

void free_prog (prog_t *prog);

void free_alls_progs (prog_t *progs);

// help

int help (void);

// main

char *my_scanf (void);

// openfile

unsigned char *filepath_to_str (char *filepath, int *size_str);

char *str_but_shorter (char *src, int size);

// open file cor

char **file_cor_to_array(char *filepath);

void disp_str_to_hexa (unsigned char *str, char *who, int size);

// other tools

char last_octet_int_to_char (int a);

void modify_str_with_bits (unsigned char *str, int bits);

// tools bit

int modify_bit_n_in_int (int nmb, int where, bool bit);

void print_char_bits (unsigned char c);

void print_int_bits (unsigned int num);

unsigned int char_nmb_to_int (unsigned char *str, int index, int size);

bool compare_bit (unsigned a, unsigned b, int size);

// execute_this_commande

void execute_this_commande (head_cor *cor, prog_t *prog);

char return_type_char (char *type);

char *type_param_to_str (unsigned char param);

int how_many_args (char *list_args);

bool check_magic (unsigned char *str, int size, char **name);

// virtual machine

prog_t *open_a_binary (char *filepath);

// op.c

void find_commandes (char *str);
