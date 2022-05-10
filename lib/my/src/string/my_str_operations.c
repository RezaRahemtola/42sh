/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** String operation functions
*/

#include <stdlib.h>

int my_strlen(char const *str)
{
    int size = 0;

    for (size = 0; str[size] != '\0'; size++);
    return (size);
}

char *my_strdup(char const *str)
{
    int size = my_strlen(str);
    char *new = malloc(sizeof(char) * (size + 1));

    if (new == NULL) {
        return (NULL);
    }
    for (int i = 0; i < size; i++) {
        new[i] = str[i];
    }
    new[size] = '\0';
    return (new);
}
