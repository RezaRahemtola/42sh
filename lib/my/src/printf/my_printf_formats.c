/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Flag formats
*/

#include "my_string.h"

int format_digit(char const *str, int index)
{
    char arr[2];

    arr[0] = str[index - 1];
    arr[1] = '\0';
    return (my_str_contains("0123456789+-#.%", arr));
}

int format_plus(char const *str, int index)
{
    char arr[2];

    arr[0] = str[index - 1];
    arr[1] = '\0';
    return (my_str_contains("0+-#%", arr));
}

int format_point(char const *str, int index)
{
    char arr[2];

    arr[0] = str[index - 1];
    arr[1] = '\0';
    return (my_str_contains("0123456789+-#%", arr));
}

int format_long(char const *str, int index)
{
    char arr[2];

    arr[0] = str[index - 1];
    arr[1] = '\0';
    return (my_str_contains("0123456789+-#.l%", arr));
}
