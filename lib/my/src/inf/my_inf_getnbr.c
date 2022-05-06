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

static int get_number(char c)
{
    int digit = -3;

    if (c == '-' || c == '+') {
        digit = (c == '-' ? -1 : -2);
    }
    for (int i = 0; i < 10; i++) {
        if (ITOC(i) == c) {
            digit = i;
        }
    }
    return (digit);
}

static char *add_digit(char *str, int digit)
{
    char *tmp = NULL;
    char *num = my_parsenbr(digit);

    tmp = my_infinmult(str, "10");
    free(str);
    str = my_infinadd(tmp, num);
    my_free(2, tmp, num);
    return (str);
}

char *my_inf_getnbr(char const *str)
{
    bool out = false;
    int less = 0;
    int num = 0;
    int len = my_strlen(str);
    char *new = my_strdup("0");

    for (int i = 0; i < len && !out && new != NULL; i++) {
        out = check_digit(get_number(str[i]), &less);
        num = get_number(str[i]);
        if (num > -1) {
            new = add_digit(new, num);
        }
    }
    return (less % 2 == 1 && new != NULL ? set_negative(new) : new);
}
