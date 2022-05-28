/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** my_is_number function
*/

#include <stdbool.h>
#include <string.h>

static bool validate_char(const char *str, size_t i, size_t *count, size_t *num)
{
    if ((str[i] == '+' || str[i] == '-') && *num == 0) {
        *count += 1;
    } else if (str[i] >= '0' && str[i] <= '9') {
        *count += 1;
        *num += 1;
    } else {
        return (true);
    }
    return (false);
}

bool my_is_number(const char *str)
{
    size_t size = strlen(str);
    size_t count = 0;
    size_t num = 0;

    for (size_t i = 0; i < size; i++)
        if (validate_char(str, i, &count, &num))
            return (false);
    return (true);
}

size_t my_nbrlen(int nb)
{
    size_t len = 1;

    while (nb > 9) {
        len++;
        nb /= 10;
    }
    return (len);
}
