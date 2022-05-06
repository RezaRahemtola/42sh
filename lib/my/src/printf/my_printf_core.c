/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Core functions
*/

#include <stdlib.h>
#include "my_printf.h"
#include "my_string.h"
#include "my.h"

static char *apply_flag(char *str, char *result, int index)
{
    char *sub = my_substr(str, 0, index);
    int size = my_strlen(sub);
    int size2 = my_strlen(result);
    char *new = malloc(sizeof(char) * (size + size2 + 1));

    for (int i = 0; i < size + size2; i++) {
        if (i < size) {
            new[i] = sub[i];
        } else {
            new[i] = result[i - size];
        }
    }
    new[size + size2] = '\0';
    free(sub);
    return (new);
}

static char *process_flag(va_list list, char *str, int pos)
{
    char *flag = NULL;
    char *result = NULL;
    char *new = NULL;
    char *end = NULL;

    if (str[pos] != '%')
        return (NULL);
    end = my_substr(str, pos, my_strlen(str));
    for (int i = 0; FLAGS[i].flag != NULL; i++) {
        if (get_flag_size(end, FLAGS[i]) > 0) {
            flag = my_substr(end, 0, get_flag_size(end, FLAGS[i]) + 1);
            result = FLAGS[i].func(list, flag);
            new = my_strrep(end, flag, result);
            my_free(3, flag, result, end);
            return (new);
        }
    }
    free(end);
    return (NULL);
}

char *print_core(char const *format, va_list list)
{
    int size = 0;
    char *copy = my_strdup(format);
    char *proc = NULL;
    char *tmp = NULL;

    size = my_strlen(copy);
    for (int i = 0; i < size; i++) {
        proc = process_flag(list, copy, i);
        if (proc != NULL) {
            tmp = apply_flag(copy, proc, i);
            free(copy);
            copy = tmp;
            size = my_strlen(copy);
        }
        free(proc);
    }
    return (copy);
}
