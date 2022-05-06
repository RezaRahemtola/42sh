/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Number flags
*/

#include <stdlib.h>
#include "my_math.h"
#include "my_printf.h"
#include "my.h"

char *flag_integer(va_list args, char *flag)
{
    int num = va_arg(args, int);
    char *parse = my_parsenbr(num);

    return (format_number(parse, flag, 0));
}

char *flag_long(va_list args, char *flag)
{
    long long num = va_arg(args, long long);
    char *parse = my_parsenbr_long(num);

    return (format_number(parse, flag, 0));
}

char *flag_unsigned(va_list args, char *flag)
{
    unsigned long long num = va_arg(args, unsigned long long);
    char *parse = my_parsenbr(num);

    return (format_number(parse, flag, 3));
}

char *flag_pointer(va_list args, char *flag)
{
    unsigned long long ptr = va_arg(args, unsigned long long);
    char *nbr = my_parsenbr_base(ptr, HEXA_LOWER_BASE);
    char *out;

    if (ptr == 0) {
        out = format_string("(nil)", flag);
        free(nbr);
    } else {
        out = format_number(nbr, flag, 4);
    }
    return (out);
}
