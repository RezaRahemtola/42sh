/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_find_prime_sup function
*/

#include <limits.h>
#include "my_math.h"

static int check_prime(int nbr, int divider)
{
    int out = 0;

    if (nbr % divider == 0) {
        out = 1;
    }
    return (out);
}

static int get_special_case(int nbr)
{
    int result = 0;

    if (nbr == 2 || nbr == 3) {
        result = 1;
    }
    return (result);
}

bool my_is_prime(int nbr)
{
    int root = 0;

    if (nbr < 4) {
        return get_special_case(nbr);
    }
    root = my_square_root(nbr);
    for (int i = 2; i <= root; i++) {
        if (check_prime(nbr, i) == 1) {
            return (false);
        }
    }
    return (true);
}

int my_find_prime_sup(int nbr)
{
    for (int i = nbr; i < INT_MAX; i++) {
        if (my_is_prime(i) == 1) {
            return (i);
        }
    }
    return (0);
}
