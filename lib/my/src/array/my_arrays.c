/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Arrays manipulation functions
*/

#include <stdarg.h>
#include <stdlib.h>

size_t my_arraylen(char *const *array)
{
    size_t size = 0;

    for (; array[size] != NULL; size++);
    return (size);
}

static void free_array(void **array)
{
    for (size_t i = 0; array[i] != NULL; i++)
        free(array[i]);
}

void my_free_arrays(size_t number, ...)
{
    va_list list;
    void **element = NULL;

    va_start(list, number);
    for (size_t i = 0; i < number; i++) {
        element = va_arg(list, void **);
        if (element != NULL)
            free_array(element);
        free(element);
    }
    va_end(list);
}
