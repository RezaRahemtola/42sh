/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_strsplit_many function
*/

#include <stdlib.h>
#include <string.h>
#include "my_string.h"

static int get_occurences(const char *str, const char *list)
{
    int count = 1;
    int new = 0;
    int old = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        new = (my_str_containschar(list, str[i]));
        if (new && !old)
            count++;
        old = new;
    }
    return (count);
}

static void append_end(const char *str, char **arr, size_t *nbr,
    const char *list)
{
    size_t length = strlen(str);
    char *array = NULL;

    if (!my_str_containschar(list, str[length - 1])) {
        array = my_substr(str, nbr[1], length);
        arr[nbr[0]] = array;
        arr[nbr[0] + 1] = NULL;
    } else {
        arr[nbr[0]] = NULL;
    }
}

char **my_strsplit_many(const char *str, const char *list)
{
    int size = get_occurences(str, list);
    size_t length = strlen(str);
    size_t info[2] = { 0, 0 };
    char **arr = malloc(sizeof(char *) * (size + 1));
    char *array = NULL;

    if (arr == NULL)
        return NULL;
    for (size_t i = 0; str[i] != '\0'; i++) {
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
