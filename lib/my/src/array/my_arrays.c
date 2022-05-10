/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Arrays manipulation functions
*/

#include <stdarg.h>
#include <stdlib.h>
#include "my_arrays.h"
#include "my_string.h"

int my_arraylen(char * const *array)
{
    int size = 0;

    for (size = 0; array[size] != NULL; size++);
    return (size);
}

static void free_array(void **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
}

void my_free_arrays(int number, ...)
{
    va_list list;
    void **element;

    va_start(list, number);
    for (int i = 0; i < number; i++) {
        element = va_arg(list, void **);
        if (element != NULL)
            free_array(element);
        free(element);
    }
    va_end(list);
}
