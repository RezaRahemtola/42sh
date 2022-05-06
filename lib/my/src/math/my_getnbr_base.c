/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_getnbr_base function
*/

#include "my_string.h"

static int check_digit(int digit, int count, int *less)
{
    int out = 0;

    if (digit < -2 || (digit < 0 && count > 0)) {
        out = 1;
    } else if (digit == -1) {
        *less += 1;
    }
    return (out);
}

static int get_number(char c, char const *base)
{
    int size = my_strlen(base);
    int digit = -3;

    if (c == '+' || c == '-') {
        digit = (c == '-' ? -1 : -2);
    }
    for (int i = 0; i < size; i++) {
        if (base[i] == c) {
            digit = i;
        }
    }
    return (digit);
}

static int finish_number(long number, int less)
{
    int final = (int) number;

    if (number > 0 && final < 0 && (final % 10 != -8 || less % 2 == 0)) {
        final = 0;
    }
    if (less % 2 == 1) {
        final = -final;
    }
    return (final);
}

static long update_number(long number, int digit, int size, int *count)
{
    number *= size;
    number += digit;
    *count += 1;
    return (number);
}

int my_getnbr_base(char const *str, char const *base)
{
    int size = my_strlen(base);
    int digit = 0;
    int less = 0;
    int out = 0;
    int count = 0;
    long number = 0;

    for (int i = 0; str[i] != '\0' && out == 0; i++) {
        digit = get_number(str[i], base);
        if (number != 0 && number * 10 / number != 10)
            return (0);
        out = check_digit(digit, count, &less);
        if (digit > -1)
            number = update_number(number, digit, size, &count);
    }
    out = finish_number(number, less);
    return (out);
}
