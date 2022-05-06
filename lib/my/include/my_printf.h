/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** printf module header
*/

#pragma once

#include <stdarg.h>

typedef struct flag_s {
    char *flag;
    char *(*func) (va_list, char *);
} flag_t;

typedef struct format_s {
    char charac;
    int (*func) (char const *, int);
} format_t;

typedef struct info_s {
    int hash;
    int plus;
    int zero;
    int num;
} info_t;

int add_hash(char const *, char *, int, info_t *);
int add_zeros(char *, char *, int, info_t *);
int get_flag_size(char *, flag_t);

char *flag_binary(va_list list, char *flag);
char *flag_character(va_list list, char *flag);
char *flag_hexa_low(va_list list, char *flag);
char *flag_hexa_up(va_list list, char *flag);
char *flag_integer(va_list list, char *flag);
char *flag_long(va_list list, char *flag);
char *flag_octal(va_list list, char *flag);
char *flag_oct_string(va_list list, char *flag);
char *flag_percentage(va_list list, char *flag);
char *flag_pointer(va_list list, char *flag);
char *flag_string(va_list list, char *flag);
char *flag_unsigned(va_list list, char *flag);

int format_digit(char const *, int);
int format_long(char const *, int);
int format_plus(char const *, int);
int format_point(char const *, int);
char *format_number(char *, char *, int);
char *format_string(char *, char *);

char *print_core(char const *format, va_list list);
char *reformat_less(char *, char *, int);
char *reformat_nonalpha(char *, int);

void identify_char(char *, int *, info_t *);
void identify_format(char *, char const *, int *, info_t *);
void process_format(char *, int, int *, int *);

static const flag_t FLAGS[15] = {
        { "ld", &flag_long },
        { "d", &flag_integer },
        { "li", &flag_long },
        { "i", &flag_integer },
        { "u", &flag_unsigned },
        { "b", &flag_binary },
        { "o", &flag_octal },
        { "x", &flag_hexa_low },
        { "X", &flag_hexa_up},
        { "c", &flag_character},
        { "s", &flag_string },
        { "S", &flag_oct_string },
        { "p", &flag_pointer},
        { "%", &flag_percentage},
        { 0, 0 }
};

static const format_t FORMATS[16] = {
        { '+', &format_plus },
        { '-', &format_plus },
        { '#', &format_plus },
        { '.', &format_point },
        { '0', &format_digit },
        { '1', &format_digit },
        { '2', &format_digit },
        { '3', &format_digit },
        { '4', &format_digit },
        { '5', &format_digit },
        { '6', &format_digit },
        { '7', &format_digit },
        { '8', &format_digit },
        { '9', &format_digit },
        { 'l', &format_long },
        { '\0', 0 }
};
