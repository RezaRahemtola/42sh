/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_strsplit function
*/

#include <stdlib.h>
#include "my_string.h"

static int get_occurences(char const *str, char separator)
{
    int count = 1;
    int new = 0;
    int old = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        new = (str[i] == separator);
        if (new == 1 && old == 0) {
            count++;
        }
        old = new;
    }
    return (count);
}

static void append_end(char const *str, char **arr, int *info, char separator)
{
    int length = my_strlen(str);
    char *array = NULL;

    if (str[length - 1] != separator) {
        array = my_substr(str, info[1], length);
        arr[info[0]] = array;
        arr[info[0] + 1] = NULL;
    } else {
        arr[info[0]] = NULL;
    }
}

char **my_strsplit(char const *str, char separator)
{
    int size = get_occurences(str, separator);
    int length = my_strlen(str);
    int info[2] = { 0, 0 };
    char **arr = malloc(sizeof(char *) * (size + 1));
    char *array = NULL;

    if (arr == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == separator && info[1] == i) {
            info[1] = i + 1;
        } else if (str[i] == separator) {
            array = my_substr_size(str, info[1], i, length);
            info[1] = i + 1;
            arr[info[0]] = array;
            info[0] += 1;
        }
    }
    append_end(str, arr, info, separator);
    return (arr);
}
