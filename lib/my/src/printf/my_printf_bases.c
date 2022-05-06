/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Bases flags
*/

#include "my_math.h"
#include "my_printf.h"
#include "my.h"

char *flag_binary(va_list args, char *flag)
{
    long long num = va_arg(args, long long);
    char *parse = my_parsenbr_base(num, BINARY_BASE);

    return (format_number(parse, flag, 3));
}

char *flag_octal(va_list args, char *flag)
{
    long long num = va_arg(args, long long);
    char *parse = my_parsenbr_base(num, OCTAL_BASE);

    return (format_number(parse, flag, 2));
}

char *flag_hexa_up(va_list args, char *flag)
{
    long long num = va_arg(args, long long);
    char *parse = my_parsenbr_base(num, HEXA_UPPER_BASE);

    return (format_number(parse, flag, 1));
}

char *flag_hexa_low(va_list args, char *flag)
{
    long long num = va_arg(args, long long);
    char *parse = my_parsenbr_base(num, HEXA_LOWER_BASE);

    return (format_number(parse, flag, 1));
}
