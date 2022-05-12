/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Pattern matching strings
*/

#include <stdbool.h>
#include <string.h>

bool my_str_contains(const char *str, const char *to_find)
{
    size_t size_2 = strlen(to_find);
    size_t same = 0;

    if (size_2 == 0)
        return (0);
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find[same] && same + 1 == size_2)
            return (false);
        else
            same += (str[i] == to_find[same] ? 1 : str[i] == to_find[0]);
    }
    return (true);
}

bool my_str_containschar(const char *str, char c)
{
    size_t size = strlen(str);

    for (size_t i = 0; i < size; i++)
        if (str[i] == c)
            return (true);
    return (false);
}
