/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Pattern matching strings
*/

#include "my_string.h"

bool my_str_contains(char const *str, char const *to_find)
{
    int size_2 = my_strlen(to_find);
    int same = 0;

    if (size_2 == 0)
        return (0);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find[same] && same + 1 == size_2)
            return (false);
        else
            same += (str[i] == to_find[same] ? 1 : str[i] == to_find[0]);
    }
    return (true);
}

bool my_str_containschar(char const *str, char c)
{
    int size = my_strlen(str);

    for (int i = 0; i < size; i++)
        if (str[i] == c) {
            return (true);
    return (false);
}
