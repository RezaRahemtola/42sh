/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_parsenbr_long function
*/

#include <stdlib.h>
#include "my_math.h"
#include "my_string.h"
#include "my.h"

static void init_array(long long nb, char *array)
{
    int old = 1;
    int digit = 0;
    char value = '\0';

    if (nb < 0) {
        nb = -nb;
        array[0] = '-';
        old++;
    }
    while (nb > 0) {
        digit = nb % 10;
        value = ITOC(digit);
        array[old - 1] = value;
        nb /= 10;
        old++;
    }
}

static char *to_string(long long nb, int zeros)
{
    int old = my_lnbrlen(nb);
    int arr_size = old + zeros + 2;
    char *array = malloc(sizeof(char) * arr_size);

    my_strfill(array, arr_size, '0');
    init_array(nb, array);
    for (int i = 0; i < zeros; i++) {
        array[old] = '0';
        old++;
    }
    array[old] = '\0';
    return (array);
}

static int get_zeros(long long nb)
{
    int count = 0;

    while (nb % 10 == 0) {
        nb /= 10;
        count++;
    }
    return (count);
}

static long reverse_number(long long nb)
{
    long long reverse = 0;

    while (nb > 0) {
        reverse *= 10;
        reverse += nb % 10;
        nb /= 10;
    }
    return (reverse);
}

char *my_parsenbr_long(long long nb)
{
    int less = 0;
    int zeros = 0;
    long long reverse = 0;
    long long final = 0;
    char *array = NULL;

    if (nb < 0) {
        nb = -nb;
        less = 1;
    } else if (nb == 0) {
        return (my_strdup("0"));
    }
    zeros = get_zeros(nb);
    reverse = reverse_number(nb);
    final = (less == 1 ? -reverse : reverse);
    array = to_string(final, zeros);
    return (array);
}
