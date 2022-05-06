/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_sort_int_array function
*/

#include <stdbool.h>

static void swap_pos(int *array, int index, int target)
{
    int temp = array[index];

    array[index] = array[target];
    array[target] = temp;
}

static bool check_array(int *array, int size)
{
    bool out = true;

    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            out = false;
            swap_pos(array, i, i + 1);
        }
    }
    return (out);
}

void my_sort_int_array(int *array, int size)
{
    bool end = false;

    while (!end) {
        end = check_array(array, size);
    }
}
