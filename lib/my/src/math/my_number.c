/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_number function
*/

#include <stddef.h>
#include "my_string.h"

char *my_number(char **ptr)
{
    char *str = ptr[0];
    int size = my_strlen(str);
    int count = 0;
    int num = 0;
    char *new = NULL;

    for (int i = 0; i < size; i++) {
        if ((str[i] == 43 || str[i] == 45) && num == 0) {
            count++;
        } else if (str[i] > 47 && str[i] < 58) {
            count++;
            num++;
        } else {
            new = my_substr_size(str, 0, count, size);
            *ptr = &str[count];
            return (new);
        }
    }
    *ptr = &str[size];
    return (my_strdup(str));
}
