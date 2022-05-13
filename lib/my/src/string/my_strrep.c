/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_strrep function
*/

#include <stdlib.h>
#include <string.h>

static char *replace(const char *str, size_t old, const char *new, size_t index)
{
    size_t size = strlen(str);
    size_t size_n = strlen(new);
    size_t total = size - old + size_n + 1;
    int j = 0;
    int k = 0;
    char *string = malloc(sizeof(char) * (total + 1));

    for (size_t i = 0; i < total; i++) {
        if (i < index) {
            string[i] = str[i];
        } else if (i < index + size_n) {
            string[i] = new[j];
            j++;
        } else {
            string[i] = str[index + old + k];
            k++;
        }
    }
    return (string);
}

char *my_strrep(const char *str, const char *pattern, const char *new)
{
    size_t size = strlen(pattern);
    size_t same = 0;

    if (size == 0)
        return (strdup(str));
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == pattern[same] && same + 1 == size)
            return (replace(str, size, new, i - size + 1));
        if (str[i] == pattern[same])
            same++;
        else
            same = (str[i] == pattern[0]) ? 1 : 0;
    }
    return (strdup(str));
}
