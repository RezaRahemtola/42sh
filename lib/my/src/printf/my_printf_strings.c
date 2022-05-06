/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** String flags
*/

#include <stdlib.h>
#include "my_printf.h"
#include "my_string.h"

char *flag_character(va_list args, char *flag)
{
    char character = va_arg(args, int);
    char *str = malloc(sizeof(char) * 2);
    char *out = NULL;

    str[0] = character;
    str[1] = '\0';
    out = format_string(str, flag);
    free(str);
    return (out);
}

char *flag_string(va_list args, char *flag)
{
    char *str = va_arg(args, char *);

    return (format_string(str, flag));
}

char *flag_oct_string(va_list args, char *flag)
{
    char *str = my_strdup(va_arg(args, char *));
    char *tmp = NULL;

    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] < 32 || str[i] > 126) {
            str = reformat_nonalpha(str, i);
        }
    }
    tmp = format_string(str, flag);
    free(str);
    return (tmp);
}

char *flag_percentage(va_list args, char *flag)
{
    char *str = my_strdup("%");

    (void) args;
    (void) flag;
    return (str);
}
