/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** printf functions
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_printf.h"
#include "my_string.h"
#include "my.h"

int my_printf(char const *format, ...)
{
    int size = 0;
    char *output = NULL;
    va_list list;

    va_start(list, format);
    output = print_core(format, list);
    va_end(list);
    my_putstr(output);
    size = my_strlen(output);
    free(output);
    return (size);
}

int my_dprintf(int fd, char const *format, ...)
{
    int size = 0;
    char *output = NULL;
    va_list list;

    va_start(list, format);
    output = print_core(format, list);
    va_end(list);
    size = my_strlen(output);
    write(fd, output, size);
    free(output);
    return (size);
}

void my_debugf(char const *format, ...)
{
    char *output = NULL;
    va_list list;

    va_start(list, format);
    output = print_core(format, list);
    va_end(list);
    write(2, output, my_strlen(output));
    free(output);
}

char *my_stringf(char const *format, ...)
{
    char *output = NULL;
    va_list list;

    va_start(list, format);
    output = print_core(format, list);
    va_end(list);
    return (output);
}
