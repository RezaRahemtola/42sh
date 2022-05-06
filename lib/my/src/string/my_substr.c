/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_substr function
*/

#include <stdlib.h>
#include "my_string.h"
#include "my.h"

char *my_substr(char const *str, int start, int end)
{
    int size = my_strlen(str);

    return (my_substr_size(str, start, end, size));
}

char *my_substr_size(char const *str, int start, int end, int size)
{
    int sub = 0;
    char *new;

    start = MAX(0, start);
    end = MIN(size, end);
    sub = end - start;
    new = malloc(sizeof(char) * (sub + 1));
    for (int i = 0; i < sub; i++) {
        new[i] = str[i + start];
    }
    new[sub] = '\0';
    return (new);
}
