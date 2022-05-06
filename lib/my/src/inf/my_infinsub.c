/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_infinsub function
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_infinite.h"
#include "my_string.h"
#include "my.h"

char *my_infinsub(char const *nbr1, char const *nbr2)
{
    char *opp = my_inf_opposite(nbr2);
    char *result = NULL;

    if (opp == NULL) {
        return (NULL);
    }
    result = my_infinadd(nbr1, opp);
    free(opp);
    return (result);
}

bool check_zero(char *str)
{
    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] != '0') {
            return (0);
        }
    }
    str[1] = '\0';
    return (1);
}

int should_swap(char const *nbr1, char const *nbr2)
{
    bool l1 = (nbr1[0] == '-');
    bool l2 = (nbr2[0] == '-');
    int out = 0;
    int result = 0;
    int s1 = 0;
    int s2 = 0;
    char *nb1 = my_inf_abs(nbr1);
    char *nb2 = my_inf_abs(nbr2);

    result = my_strcmp(nb1, nb2);
    s1 = my_strlen(nb1);
    s2 = my_strlen(nb2);
    if ((result < 0 && s2 >= s1) || (s1 < s2 && l1 != l2)) {
        out = 1;
    } else {
        out = -1;
    }
    my_free(2, nb1, nb2);
    return (out);
}
