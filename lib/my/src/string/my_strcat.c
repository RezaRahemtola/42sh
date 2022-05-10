/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_strcat function
*/

#include <stdlib.h>
#include "my_string.h"
#include "my.h"

char *my_strcat(char const *src, char const *src2)
{
    int size = my_strlen(src);
    int size2 = my_strlen(src2);
    char *new = malloc(size + size2 + 1);

    for (int i = 0; i < size + size2; i++) {
        if (i < size) {
            new[i] = src[i];
        } else {
            new[i] = src2[i - size];
        }
    }
    new[size + size2] = '\0';
    return (new);
}
