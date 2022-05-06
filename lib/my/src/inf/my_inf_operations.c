/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Infinite operations
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_infinite.h"
#include "my_string.h"
#include "my.h"

static char *make_addition(char *result)
{
    char *str = my_infinadd(result, "1");

    free(result);
    return (str);
}

static char *make_division(char *nb, char const *x)
{
    char *str = my_infindiv(nb, x);

    free(nb);
    return (str);
}

char *my_inf_log(char const *nbr, char const *x)
{
    bool zero = (my_inf_cmp("0", nbr) > -1 || my_inf_cmp("0", x) > -1);
    char *nb = my_strdup(nbr);
    char *result = my_strdup("0");

    if (nb == NULL || x == NULL) {
        return (my_free_null(2, nb, result));
    }
    for (int i = 0; my_inf_cmp(nb, x) != -1 && !zero; i++) {
        result = make_addition(result);
        nb = make_division(nb, x);
        if (result == NULL || nb == NULL) {
            return (my_free_null(2, nb, result));
        }
    }
    free(nb);
    return (result);
}

char *my_inf_power(char *nbr, char *p)
{
    char *result = NULL;
    char *less = NULL;
    char *pow = NULL;

    if (my_strcmp(p, "0") == 0) {
        return (my_strdup("1"));
    } else if (p[0] == '-') {
        return (my_strdup("0"));
    }
    less = my_infinadd(p, "-1");
    if (less == NULL) {
        return (NULL);
    }
    pow = my_inf_power(nbr, less);
    if (pow == NULL) {
        return (my_free_null(1, less));
    }
    result = my_infinmult(nbr, pow);
    my_free(2, less, pow);
    return (result);
}
