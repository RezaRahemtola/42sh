/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_strcmp function
*/

#include "my_string.h"

static int check_size(char const *str, int size, int nbr)
{
    char result = 0;

    if (size <= nbr)
        result = str[size];
    return (result);
}

int my_strcmp(char const *str1, char const *str2)
{
    int size = my_strlen(str1);
    int size2 = my_strlen(str2);
    int result = 0;

    for (int i = 0; str1[i] != '\0' && str2[i] != '\0' && result == 0; i++) {
        if (str1[i] != str2[i]) {
            result = str1[i] - str2[i];
        }
    }
    if (result == 0 && size > size2) {
        result = check_size(str1, size2, size);
    } else if (result == 0 && size < size2) {
        result = check_size(str2, size, size) * -1;
    }
    return (result);
}

int my_strncmp(char const *str1, char const *str2, int n)
{
    int result = 0;

    for (int i = 0; i < n && str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i] && result == 0) {
            result = str1[i] - str2[i];
        }
    }
    if (result == 0 ){
        result = check_size(str1, my_strlen(str2), n);
    }
    return (result);
}
