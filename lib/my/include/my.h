/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Functions header
*/

#pragma once

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define CTOI(x) ((x) - '0')
#define ITOC(x) ((x) + '0')
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

static const char * const BINARY_BASE = "01";
static const char * const OCTAL_BASE = "01234567";
static const char * const HEXA_LOWER_BASE = "0123456789abcdef";
static const char * const HEXA_UPPER_BASE = "0123456789ABCDEF";

void my_putchar(char c);
void my_putnbr(int nbr);
void my_putstr(char const *str);

int my_dprintf(int fd, char const *format, ...);
int my_printf(char const *format, ...);
void my_debugf(char const *format, ...) \
__attribute__ ((deprecated("Use of a debug function")));
char *my_stringf(char const *format, ...);

void my_free(int size, ...);
void *my_free_null(int size, ...);
void my_free_arrays(int size, ...);
