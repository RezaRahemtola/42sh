/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Format flag formatter
*/

#include <stdlib.h>
#include "my.h"
#include "my_math.h"
#include "my_string.h"

static char *reformat_octal(char *str)
{
    int size = my_strlen(str);
    int new = MAX(5, size + 2);
    char *array = malloc(sizeof(char) * new);

    my_strfill(array, new, '0');
    array[0] = '\\';
    for (int i = 0; i < size; i++) {
        array[MAX(1, 4 - size) + i] = str[i];
    }
    array[MAX(4, size + 1)] = '\0';
    return (array);
}

char *reformat_less(char *str, char *initial, int zero)
{
    char *new;
    int out = 0;

    for (int i = 0; i < my_strlen(str) && out == 0; i++) {
        if (str[i] == '-' && zero > my_strlen(initial) - 1) {
            str[i] = '0';
            out++;
        }
    }
    if (out == 1) {
        new = malloc(sizeof(char) * (my_strlen(str) + 2));
        new[0] = '-';
        for (int i = 0; i < my_strlen(str); i++) {
            new[i + 1] = str[i];
        }
        new[my_strlen(str) + 1] = '\0';
        return (new);
    }
    return (my_strdup(str));
}

char *reformat_nonalpha(char *str, int index)
{
    char *sub = my_substr(str, index, index + 1);
    char *oct = my_parsenbr_base(str[index], "01234567");
    char *ref = reformat_octal(oct);
    char *new = my_strrep(str, sub, ref);

    free(str);
    free(ref);
    free(sub);
    free(oct);
    return (new);
}
