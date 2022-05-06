/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_parsenbr function
*/

#include <stdlib.h>
#include "my_math.h"
#include "my_string.h"
#include "my.h"

static void init_array(long nb, char *array)
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

static char *to_string(long nb, int zeros)
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

static int get_zeros(int nb)
{
    int num = nb;
    int count = 0;

    while (num % 10 == 0) {
        num /= 10;
        count++;
    }
    return (count);
}

static long reverse_number(long nb)
{
    long reverse = 0;

    while (nb > 0) {
        reverse *= 10;
        reverse += nb % 10;
        nb /= 10;
    }
    return (reverse);
}

char *my_parsenbr(int nb)
{
    int less = 0;
    int zeros = 0;
    long num = (long) nb;
    long reverse = 0;
    long final = 0;
    char *array = NULL;

    if (num < 0) {
        num = -num;
        less = 1;
    } else if (num == 0) {
        return (my_strdup("0"));
    }
    zeros = get_zeros((int) num);
    reverse = reverse_number(num);
    final = (less == 1 ? -reverse : reverse);
    array = to_string(final, zeros);
    return (array);
}
