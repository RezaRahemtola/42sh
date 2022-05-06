/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_show_word_array function
*/

#include "my_arrays.h"
#include "my.h"

int my_show_word_array(char * const *array)
{
    int size = my_arraylen(array);

    for (int i = 0; i < size; i++) {
        my_printf("%s\n", array[i]);
    }
    return (0);
}
