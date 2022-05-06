/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_inf_parsenbr_base function
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_infinite.h"
#include "my_math.h"
#include "my_string.h"
#include "my.h"

static char *make_operation(char *nb, char *array, char const **bases, int old)
{
    char value = '\0';
    char *digit = my_infinmod(nb, bases[1]);
    char *result = NULL;

    if (digit == NULL) {
        return my_free_null(2, nb, digit);
    }
    value = bases[0][my_getnbr(digit)];
    array[old] = value;
    result = my_infindiv(nb, bases[1]);
    my_free(2, nb, digit);
    return (result);
}

static void init_array(char *nb, char *array, char const *base, \
char const *size)
{
    bool less = (nb[0] == '-');
    int i = 0;
    char const *bases[2] = { base, size };

    nb = my_inf_abs(nb);
    for (i = 0; my_inf_cmp(nb, "0") > 0 && nb != NULL; i++) {
        nb = make_operation(nb, array, bases, i);
    }
    if (less) {
        array[i] = '-';
        i++;
    }
    array[i] = '\0';
    free(nb);
}

static char *to_string(char *nb, char const *base, char const *size)
{
    char *abs = my_inf_abs(nb);
    char *log = NULL;
    char *array = NULL;

    if (abs == NULL) {
        return (NULL);
    }
    log = my_inf_log(abs, size);
    if (log == NULL) {
        return my_free_null(1, abs);
    }
    array = malloc(sizeof(char) * my_getnbr(log) + 3);
    if (array == NULL) {
        return my_free_null(2, abs, log);
    }
    init_array(nb, array, base, size);
    my_free(2, abs, log);
    return (my_revxstr(array));
}

char *my_inf_parsenbr_base(char const *nbr, char const *base)
{
    char *result = NULL;
    char *copy = my_strdup(nbr);
    char *parse = my_parsenbr(my_strlen(base));

    if (copy == NULL || parse == NULL) {
        return (my_free_null(2, copy, parse));
    }
    if (my_strcmp(nbr, "0") == 0) {
        result = malloc(sizeof(char) * 2);
        if (result != NULL) {
            result[0] = base[0];
            result[1] = '\0';
        }
        free(copy);
        return (result);
    }
    result = to_string(copy, base, parse);
    free(parse);
    return (result);
}
