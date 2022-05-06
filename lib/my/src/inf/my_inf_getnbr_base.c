/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_getnbr_base_inf function
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_infinite.h"
#include "my_math.h"
#include "my_string.h"
#include "my.h"

static char *set_negative(char *number)
{
    char *negative = my_inf_opposite(number);

    free(number);
    return (negative);
}

static bool check_digit(int digit, int *less)
{
    bool out = false;

    if (digit < -2) {
        out = true;
    } else if (digit == -1) {
        *less += 1;
    }
    return (out);
}

static int get_number(char c, char const *base)
{
    int size = my_strlen(base);
    int digit = -3;

    if (c == '-' || c == '+') {
        digit = (c == '-' ? -1 : -2);
    }
    for (int i = 0; i < size; i++) {
        if (base[i] == c) {
            digit = i;
        }
    }
    return (digit);
}

static char *add_digit(char *str, char const *size, int digit)
{
    char *number = my_parsenbr(digit);
    char *mult = my_infinmult(str, size);
    char *new = my_infinadd(mult, number);

    my_free(3, number, mult, str);
    return (new);
}

char *my_inf_getnbr_base(char const *str, char const *base)
{
    bool out = false;
    int less = 0;
    int num = 0;
    int len = my_strlen(str);
    char *new = my_strdup("0");
    char *size = my_parsenbr(my_strlen(base));

    if (new == NULL || size == NULL) {
        return (my_free_null(2, new, size));
    }
    for (int i = 0; i < len && !out && new != NULL; i++) {
        out = check_digit(get_number(str[i], base), &less);
        num = get_number(str[i], base);
        if (num > -1) {
            new = add_digit(new, size, num);
        }
    }
    free(size);
    return (less % 2 == 1 && new != NULL ? set_negative(new) : new);
}
