/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** String standard functions
*/

#include <stdbool.h>

bool my_str_isalpha(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') {
            return (false);
        }
    }
    return (true);
}

bool my_str_islower(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 'a' || str[i] > 'z') {
            return (false);
        }
    }
    return (true);
}

bool my_str_isnum(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return (false);
        }
    }
    return (true);
}

bool my_str_isprintable(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 32 || str[i] == 127) {
            return (false);
        }
    }
    return (true);
}

bool my_str_isupper(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 'A' || str[i] > 'Z') {
            return (false);
        }
    }
    return (true);
}
