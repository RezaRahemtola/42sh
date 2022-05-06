/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_is_number function
*/

#include <stdbool.h>
#include "my_string.h"

static int validate_char(char const *str, int i, int *count, int *num)
{
    if ((str[i] == '+' || str[i] == '-') && *num == 0) {
        *count += 1;
    } else if (str[i] >= '0' && str[i] <= '9') {
        *count += 1;
        *num += 1;
    } else {
        return (1);
    }
    return (0);
}

bool my_is_number(char *str)
{
    int size = my_strlen(str);
    int count = 0;
    int num = 0;

    for (int i = 0; i < size; i++) {
        if (validate_char(str, i, &count, &num)) {
            return (false);
        }
    }
    return (true);
}
