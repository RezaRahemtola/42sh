/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_infinmult function
*/

#include <stdlib.h>
#include "my_string.h"
#include "my.h"

int check_zero(char *str);
int should_swap(char const *nbr1, char const *nbr2);

static void finish_number(char *str, int less)
{
    int j = 0;
    int last = 0;

    if (check_zero(str)) {
        return;
    }
    for (j = 0; j < my_strlen(str); j++) {
        if (str[j] != '0') {
            last = j + 1;
        }
    }
    if (less > 0) {
        str[last] = '-';
        last++;
    }
    str[last] = '\0';
}

static void multiply_number(char *str, char *nbr1, char *nbr2, int less)
{
    int num = 0;
    int acc = 0;
    int count = 0;

    for (int j = 0; j < my_strlen(nbr2) && nbr2[j] != '-'; j++) {
        for (int i = 0; i < my_strlen(nbr1) && nbr1[i] != '-'; i++) {
            num = acc + CTOI(str[i + j]) + CTOI(nbr2[j]) * CTOI(nbr1[i]);
            str[i + j] = ITOC(num % 10);
            acc = num / 10;
            count = MAX(count, i + j + 1);
        }
        str[count] = ITOC(acc);
        acc = 0;
    }
    finish_number(str, less);
}

char *my_infinmult(char const *nbr1, char const *nbr2)
{
    int size = my_strlen(nbr1) + my_strlen(nbr2);
    int less1 = (nbr1[0] == '-' ? 1 : 0);
    int less2 = (nbr2[0] == '-' ? 1 : 0);
    int sw = should_swap(nbr1, nbr2);
    char *str = malloc(sizeof(char) * (size + 1));
    char *nb1 = my_revstr(nbr1);
    char *nb2 = my_revstr(nbr2);

    my_strfill(str, size + 1, '0');
    if (less1 == less2) {
        multiply_number(str, (sw == 1 ? nb2 : nb1), (sw == 1 ? nb1 : nb2), 0);
    } else {
        multiply_number(str, (sw == 1 ? nb2 : nb1), (sw == 1 ? nb1 : nb2), 1);
    }
    my_free(2, nb1, nb2);
    return (my_revxstr(str));
}
