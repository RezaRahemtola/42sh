/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Reverse string functions
*/

#include <stddef.h>
#include "my_string.h"

char *my_revxstr(char *str)
{
    int size = my_strlen(str);
    char arr[size];
    int a = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        arr[a] = str[size - i - 1];
        a++;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = arr[i];
    }
    return (str);
}

char *my_revstr(char const *str)
{
    char *dup = my_strdup(str);

    if (dup != NULL) {
        dup = my_revxstr(dup);
    }
    return (dup);
}
