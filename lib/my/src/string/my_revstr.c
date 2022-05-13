/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Reverse string functions
*/

#include <stddef.h>
#include <string.h>

static char *my_revxstr(char *str)
{
    int size = strlen(str);
    char arr[size];
    int a = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        arr[a] = str[size - i - 1];
        a++;
    }
    for (size_t i = 0; str[i] != '\0'; i++)
        str[i] = arr[i];
    return (str);
}

char *my_revstr(const char *str)
{
    char *dup = strdup(str);

    if (dup != NULL)
        dup = my_revxstr(dup);
    return (dup);
}
