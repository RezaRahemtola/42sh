/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_strsplit_many function
*/

#include <stdlib.h>
#include "my_string.h"

static int get_occurences(char const *str, char const *list)
{
    int count = 1;
    int new = 0;
    int old = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        new = (my_str_containschar(list, str[i]));
        if (new && !old) {
            count++;
        }
        old = new;
    }
    return (count);
}

static void append_end(char const *str, char **arr, int *nbr, char const *list)
{
    int length = my_strlen(str);
    char *array = NULL;

    if (!my_str_containschar(list, str[length - 1])) {
        array = my_substr(str, nbr[1], length);
        arr[nbr[0]] = array;
        arr[nbr[0] + 1] = NULL;
    } else {
        arr[nbr[0]] = NULL;
    }
}

char **my_strsplit_many(char const *str, char const *list)
{
    int size = get_occurences(str, list);
    int length = my_strlen(str);
    int info[2] = { 0, 0 };
    char **arr = malloc(sizeof(char *) * (size + 1));
    char *array = NULL;

    if (arr == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (my_str_containschar(list, str[i]) && info[1] == i) {
            info[1] = i + 1;
        } else if (my_str_containschar(list, str[i])) {
            array = my_substr_size(str, info[1], i, length);
            info[1] = i + 1;
            arr[info[0]] = array;
            info[0] += 1;
        }
    }
    append_end(str, arr, info, list);
    return (arr);
}
