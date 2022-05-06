/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_parsenbr_base function
*/

#include <stdlib.h>
#include "my_math.h"
#include "my_string.h"
#include "my.h"

static void init_array(long nb, char *array, char const *base, int size)
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
        digit = nb % size;
        value = base[digit];
        array[old - 1] = value;
        nb /= size;
        old++;
    }
}

static char *to_string(long nb, int zeros, char const *base, int size)
{
    int old = my_llog(ABS(nb), size) + 2;
    int arr_size = old + zeros + 1;
    char *array = malloc(sizeof(char) * arr_size);

    my_strfill(array, arr_size - 1, '0');
    init_array(nb, array, base, size);
    for (int i = 0; i < zeros; i++) {
        array[old - 1] = base[0];
        old++;
    }
    array[old] = '\0';
    return (array);
}

static int get_zeros(int nb, char const *base, int size)
{
    int num = nb;
    int count = 0;

    while (base[num % size] == base[0]) {
        num /= size;
        count++;
    }
    return (count);
}

static long reverse_number(long nb, int size)
{
    long reverse = 0;

    while (nb > 0) {
        reverse *= size;
        reverse += nb % size;
        nb /= size;
    }
    return (reverse);
}

char *my_parsenbr_base(int nb, char const *base)
{
    int less = 0;
    int zeros = 0;
    long num = (long) nb;
    long reverse = 0;
    long final = 0;

    if (num < 0) {
        num = -num;
        less = 1;
    } else if (num == 0) {
        char *zero = malloc(sizeof(char) * 2);
        zero[0] = base[0];
        zero[1] = '\0';
        return (zero);
    }
    zeros = get_zeros((int) num, base, my_strlen(base));
    reverse = reverse_number(num, my_strlen(base));
    final = (less == 1 ? -reverse : reverse);
    return (to_string(final, zeros, base, my_strlen(base)));
}
