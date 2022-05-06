/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_sort_string_array function
*/

#include <stdbool.h>
#include "my_arrays.h"
#include "my_string.h"

static void swap_pos(char **array, int index, int target)
{
    char *temp = array[index];

    array[index] = array[target];
    array[target] = temp;
}

static int check_array(char **array, int size)
{
    bool out = true;

    for (int i = 0; i < size - 1; i++) {
        if (my_strcmp(array[i], array[i + 1]) > 0) {
            out = false;
            swap_pos(array, i, i + 1);
        }
    }
    return (out);
}

void my_sort_string_array(char **array)
{
    bool end = false;
    int size = my_arraylen(array);

    while (!end) {
        end = check_array(array, size);
    }
}
