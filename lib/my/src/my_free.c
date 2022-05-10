/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_free function
*/

#include <stdarg.h>
#include <stdlib.h>

void my_free(int number, ...)
{
    va_list list;
    void *element = NULL;

    va_start(list, number);
    for (int i = 0; i < number; i++) {
        element = va_arg(list, void *);
        free(element);
    }
    va_end(list);
}
