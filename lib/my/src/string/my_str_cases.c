/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** String cases manipulation
*/

#include <stddef.h>
#include "my_string.h"

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
    return (str);
}

char *my_strxlowcase(char const *str)
{
    char *dup = my_strdup(str);

    if (dup == NULL) {
        return (NULL);
    }
    return (my_strlowcase(dup));
}

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
    return (str);
}

char *my_strxupcase(char const *str)
{
    char *dup = my_strdup(str);

    if (dup == NULL) {
        return (NULL);
    }
    return (my_strupcase(dup));
}
