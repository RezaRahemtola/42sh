/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** my_strcontainsany function
*/

#include <stdbool.h>
#include <string.h>

bool my_str_starts(const char *str, const char *to_find)
{
    size_t size = strlen(str);
    size_t size_2 = strlen(to_find);
    size_t same = 0;

    for (size_t i = 0; i < size && i < size_2; i++)
        if (str[i] == to_find[i])
            same++;
    return (same != size_2);
}
