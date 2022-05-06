/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_strcapitalize function
*/

#include <stdbool.h>
#include <stddef.h>
#include "my_string.h"

static bool is_letter(char c)
{
    bool result = false;
    bool lower = (c >= 'a' && c <= 'z');
    bool upper = (c >= 'A' && c <= 'Z');
    bool digit = (c >= '0' && c <= '9');

    if (lower || upper || digit) {
        result = true;
    }
    return (result);
}

char *my_strxcapitalize(char *str)
{
    bool space = false;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z' && (!space || i == 0)) {
            space = true;
            str[i] = str[i] - 32;
        } else if (space && str[i] >= 'A' && str[i] <= 'Z' && i > 0) {
            str[i] = str[i] + 32;
        } else {
            space = is_letter(str[i]);
        }
    }
    return (str);
}

char *my_strcapitalize(char const *str)
{
    char *dup = my_strdup(str);

    if (dup == NULL) {
        return (NULL);
    }
    return (my_strxcapitalize(dup));
}
