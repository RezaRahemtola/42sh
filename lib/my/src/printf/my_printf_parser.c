/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Format flags parser
*/

#include <stdlib.h>
#include "my.h"
#include "my_math.h"
#include "my_printf.h"
#include "my_string.h"

static char *init_number_array(char *str, int hex, info_t *info)
{
    int index = 0;
    int size = my_strlen(str) + info->num + info->zero + 6;
    char *array = malloc(sizeof(char) * size + 1);

    my_strfill(array, size, ' ');
    index += add_hash(str, array, hex, info);
    index += add_zeros(str, array, hex, info);
    for (int i = 0; i < my_strlen(str); i++) {
        array[index + i] = str[i];
    }
    array[index + my_strlen(str)] = '\0';
    return (array);
}

int get_flag_size(char *str, flag_t flag)
{
    int out = 0;
    int size = 0;

    for (int i = 1; i < my_strlen(str) && out == 0; i++) {
        if (my_str_starts(&str[i], flag.flag) == 0) {
            return (size + my_strlen(flag.flag));
        } else {
            process_format(str, i, &size, &out);
        }
    }
    return (0);
}

void process_format(char *str, int index, int *size, int *out)
{
    char charac;

    for (int i = 0; FORMATS[i].charac != '\0'; i++) {
        charac = FORMATS[i].charac;
        if (str[index] == charac && FORMATS[i].func(str, index) == 0) {
            *size = *size + 1;
            return;
        }
    }
    *out = 1;
}

char *format_string(char *str, char *flag)
{
    int str_size = my_strlen(str);
    int size = 0;
    int less = 0;
    char *array = NULL;

    for (int i = 1; i < my_strlen(flag); i++) {
        less += (flag[i] == '-' ? 1 : 0);
        if (size == 0 && flag[i] >= '0' && flag[i] <= '9') {
            array = my_substr(flag, i, my_strlen(flag));
            size = my_getnbr(array);
            free(array);
        }
    }
    array = malloc(sizeof(char) * (MAX(size, str_size) + 1));
    my_strfill(array, MAX(size, str_size) + 1, ' ');
    for (int i = 0; i < str_size; i++) {
        array[(less > 0 ? 0 : MAX(0, size - str_size)) + i] = str[i];
    }
    return (array);
}

char *format_number(char *str, char *flag, int hex)
{
    int arr_size = my_strlen(flag);
    char *array = NULL;
    char *reformat = NULL;
    char *format = NULL;
    info_t info = { 0, 0, -2, -2 };

    for (int i = 1; i < arr_size; i++) {
        identify_char(flag, &i, &info);
    }
    info.hash = (flag[arr_size - 1] == 'X' && info.hash > 0 ? -1 : info.hash);
    array = init_number_array(str, hex, &info);
    reformat = reformat_less(array, str, info.num);
    format = format_string(reformat, flag);
    free(reformat);
    free(array);
    free(str);
    return (format);
}
