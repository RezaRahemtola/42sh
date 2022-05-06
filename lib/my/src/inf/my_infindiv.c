/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_infindiv function
*/

#include <stdlib.h>
#include "my_infinite.h"
#include "my_math.h"
#include "my_string.h"
#include "my.h"

int check_zero(char *str);

static int get_count(char *nb, char *divider)
{
    int count = 0;
    char *number = my_strdup(nb);
    char *tmp = NULL;

    for (int i = 0; my_inf_cmp(number, divider) >= 0; i++) {
        tmp = my_infinsub(number, divider);
        free(number);
        number = tmp;
        count++;
    }
    free(number);
    return (count);
}

static char *make_operation(char *acc, char *str, char *nbr2, int index)
{
    int count = get_count(acc, nbr2);
    char *parse = my_parsenbr(count);
    char *mult = my_infinmult(nbr2, parse);
    char *sub = my_infinsub(acc, mult);

    str[index] = ITOC(count);
    my_free(2, parse, mult);
    return (sub);
}

static void finish_number(char *str, int less)
{
    int last = 0;

    str = my_revxstr(str);
    if (check_zero(str))
        return;
    for (int j = 0; j < my_strlen(str); j++) {
        if (str[j] != '0') {
            last = j + 1;
        }
    }
    if (less > 0) {
        str[last] = '-';
        last++;
    }
    str[last] = '\0';
    str = my_revxstr(str);
    for (int i = my_strlen(str) - 1; i >= 0; i--) {
        if (str[i] == 'a')
            str[i] = '\0';
    }
}

static void divide_number(char *str, char *nbr1, char *nbr2, int less)
{
    int i = 0;
    int size = my_strlen(nbr1);
    char *acc = my_strdup("0");
    char *add = NULL;
    char *mult = NULL;
    char digit[2];

    digit[1] = '\0';
    for (i = 0; i < size; i++) {
        digit[0] = nbr1[i];
        mult = my_infinmult(acc, "10");
        add = my_infinadd(mult, digit);
        free(acc);
        acc = make_operation(add, str, nbr2, i);
        my_free(2, add, mult);
    }
    free(acc);
    finish_number(str, less);
}

char *my_infindiv(char const *nbr1, char const *nbr2)
{
    int size = MAX(my_strlen(nbr1), my_strlen(nbr2));
    int less1 = (nbr1[0] == '-' ? 1 : 0);
    int less2 = (nbr2[0] == '-' ? 1 : 0);
    char *str = malloc(sizeof(char) * (size + 1));
    char *nb1 = my_inf_abs(nbr1);
    char *nb2 = my_inf_abs(nbr2);

    if (my_strcmp(nb2, "0") == 0) {
        return NULL;
    }
    my_strfill(str, size + 1, 'a');
    divide_number(str, nb1, nb2, (less1 == less2 ? 0 : 1));
    my_free(2, nb1, nb2);
    return (str);
}
