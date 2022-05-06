/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_inf_cmp function
*/

#include <stdbool.h>
#include "my_string.h"

static bool is_minor(int s1, int s2, bool l1, bool l2)
{
    return ((l1 && l2 && s1 > s2) || (l1 && !l2) || (!l1 && !l2 && s1 < s2));
}

static bool is_cmp(char const *nb1, char const *nb2, bool l1, bool l2)
{
    int cmp = my_strcmp(nb1, nb2);
    int s1 = my_strlen(nb1);
    int s2 = my_strlen(nb2);
    bool negative = (l1 && s1 == s2 && cmp >= 1);
    bool positive = (!l1 && !l2 && s1 == s2 && cmp <= -1);

    if (negative || positive) {
        return (true);
    } else {
        return (false);
    }
}

int my_inf_cmp(char const *nbr1, char const *nbr2)
{
    bool l1 = (nbr1[0] == '-');
    bool l2 = (nbr2[0] == '-');
    int out = 0;
    int s1 = my_strlen(nbr1);
    int s2 = my_strlen(nbr2);

    if (l1) {
        nbr1++;
    }
    if (l2) {
        nbr2++;
    }
    if (l1 == l2 && my_strcmp(nbr1, nbr2) == 0) {
        out = 0;
    } else if (is_minor(s1, s2, l1, l2) || is_cmp(nbr1, nbr2, l1, l2)) {
        out = -1;
    } else {
        out = 1;
    }
    return (out);
}

char *my_inf_opposite(char const *nbr)
{
    if (my_strcmp(nbr, "0") == 0) {
        return (my_strdup("0"));
    } else if (nbr[0] == '-') {
        return (my_substr(nbr, 1, my_strlen(nbr)));
    } else {
        return (my_strcat("-", nbr));
    }
}

char *my_inf_abs(char const *nbr)
{
    if (nbr[0] == '-') {
        return (my_inf_opposite(nbr));
    } else {
        return (my_strdup(nbr));
    }
}
