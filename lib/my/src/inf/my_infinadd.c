/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_infinadd function
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_string.h"
#include "my.h"

int check_zero(char *str);
int should_swap(char const *nbr1, char const *nbr2);

static void finish_number(char *str, int acc, int i, int less)
{
    int last = i;

    if (acc > 0) {
        str[i] = ITOC(acc);
        i++;
    }
    if (check_zero(str))
        return;
    for (int j = 0; j < my_strlen(str); j++) {
        if (str[j] != '0')
            last = j + 1;
    }
    if (less > 0) {
        str[last] = '-';
        last++;
    }
    str[last] = '\0';
}

static void add_number(char *str, char *nbr1, char *nbr2, int less)
{
    int i = 0;
    int num = 0;
    int acc = 0;
    int size1 = my_strlen(nbr1);
    int size2 = my_strlen(nbr2);
    int max = MAX(size1, size2);

    for (i = 0; i < max; i++) {
        num = acc;
        if (i < size1 && nbr1[i] != '-')
            num += CTOI(nbr1[i]);
        if (i < size2 && nbr2[i] != '-')
            num += CTOI(nbr2[i]);
        str[i] = ITOC(num % 10);
        acc = num / 10;
    }
    finish_number(str, acc, i, less);
}

static void sub_number(char *str, char *nbr1, char *nbr2, int less)
{
    int i = 0;
    int num = 0;
    int acc = 0;
    int max = MAX(my_strlen(nbr1), my_strlen(nbr2));

    for (i = 0; i < max; i++) {
        num = -acc;
        acc = 0;
        if (i < my_strlen(nbr1) && nbr1[i] != '-')
            num += CTOI(nbr1[i]);
        if (i < my_strlen(nbr2) && nbr2[i] != '-')
            num -= CTOI(nbr2[i]);
        if (num < 0) {
            acc++;
            num += 10;
        }
        str[i] = ITOC(num % 10);
    }
    finish_number(str, acc, i, less);
}

char *my_infinadd(char const *nbr1, char const *nbr2)
{
    bool less1 = (nbr1[0] == '-');
    bool less2 = (nbr2[0] == '-');
    int size = MAX(my_strlen(nbr1), my_strlen(nbr2));
    int sw = should_swap(nbr1, nbr2);
    int less = (less2 == 1 ? sw : -sw);
    char *str = malloc(sizeof(char) * (size + 2));
    char *nb1 = my_revstr(nbr1);
    char *nb2 = my_revstr(nbr2);

    if (str == NULL || nb1 == NULL || nb2 == NULL) {
        return (my_free_null(3, str, nb1, nb2));
    }
    my_strfill(str, size + 2, '0');
    if (less1 == less2) {
        add_number(str, nb1, nb2, less1);
    } else {
        sub_number(str, (sw == 1 ? nb2 : nb1), (sw == 1 ? nb1 : nb2), less);
    }
    my_free(2, nb1, nb2);
    return (my_revxstr(str));
}
