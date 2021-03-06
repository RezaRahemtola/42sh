/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** my_substr function
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

char *my_substr_size(const char *str, size_t start, size_t end, size_t size)
{
    size_t sub = 0;
    char *new = NULL;

    start = MAX(0, (int)start);
    end = MIN((int)size, (int)end);
    sub = end - start;
    new = malloc(sizeof(char) * (sub + 1));
    for (size_t i = 0; i < sub; i++)
        new[i] = str[i + start];
    new[sub] = '\0';
    return (new);
}

char *my_substr(const char *str, int start, int end)
{
    size_t size = strlen(str);

    return (my_substr_size(str, start, end, size));
}
