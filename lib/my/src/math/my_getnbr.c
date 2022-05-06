/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_getnbr function
*/

static void check_digit(int digit, int *out, int *less, int count)
{
    *out = digit < 0 || (digit > 10 && count > 0) ? 1 : 0;
    *less = (digit == 11 ? *less + 1 : *less);
}

static int get_number(char c)
{
    int digit = -1;

    if (c == '+' || c == '-') {
        digit = (c == '-' ? 11 : 12);
    } else if (c >= '0' && c <= '9') {
        digit = c - '0';
    }
    return (digit);
}

static int finish_number(long number, int less)
{
    int final = (int) number;

    if (number > 0 && final < 0 && (final % 10 != -8 || less % 2 == 0)) {
        final = 0;
    } else if (less % 2 == 1) {
        final = -final;
    }
    return (final);
}

int my_getnbr(char const *str)
{
    int digit = 0;
    int less = 0;
    int out = 0;
    int count = 0;
    long number = 0;

    for (int i = 0; str[i] != '\0' && out == 0; i++) {
        digit = get_number(str[i]);
        if (number != 0 && (int) number * 10 / number != 10) {
            return (0);
        }
        check_digit(digit, &out, &less, count);
        if (digit > -1 && digit < 10) {
            number = number * 10 + digit;
            count++;
        }
    }
    out = finish_number(number, less);
    return (out);
}
