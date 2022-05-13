/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** String standard functions
*/

#include <stdbool.h>

bool my_char_isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (true);
    return (false);
}
