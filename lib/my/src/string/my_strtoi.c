/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_number function
*/

#include <stdlib.h>
#include "my_math.h"
#include "my_string.h"

static int get_number(char *str, int count)
{
    char *new = my_substr(str, 0, count);
    int result = my_getnbr(new);

    free(new);
    return (result);
}

int my_strtoi(char **ptr)
{
    char *str = ptr[0];
    int size = my_strlen(str);
    int count = 0;
    int num = 0;

    for (int i = 0; i < size; i++) {
        if ((str[i] == 45 || str[i] == 43) && num == 0) {
            count++;
        } else if (str[i] > 47 && str[i] < 58) {
            count++;
            num++;
        } else {
            *ptr = &str[count];
            return (get_number(str, count));
        }
    }
    *ptr = &str[size];
    return my_getnbr(str);
}
