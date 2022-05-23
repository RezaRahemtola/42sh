/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Pattern matching strings
*/

#include <stdbool.h>
#include <string.h>

bool my_str_containschar(const char *str, char c)
{
    size_t size = strlen(str);

    for (size_t i = 0; i < size; i++)
        if (str[i] == c)
            return (true);
    return (false);
}
