/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Info struct maker
*/

#include <stdlib.h>
#include "my_math.h"
#include "my_printf.h"
#include "my_string.h"

int add_hash(char const *str, char *array, int hex, info_t *info)
{
    int index = 0;

    if (str[0] != '-' && info->plus > 0 && (hex == 0 || hex == 4)) {
        array[index] = '+';
        index++;
    }
    if ((str[0] != '0' && info->hash != 0 && hex == 1) || hex == 4) {
        array[index] = '0';
        array[index + 1] = info->hash == -1 ? 'X' : 'x';
        index += 2;
    } else if (str[0] != '0' && info->hash > 0 && hex == 2) {
        array[index] = '0';
        index++;
    }
    return (index);
}

int add_zeros(char *str, char *array, int hex, info_t *info)
{
    int result = 0;
    int index = 0;
    int m = (hex == 2 && info->hash > 0 && str[0] == '0' ? 1 : 0);

    for (int i = 0; array[i] != ' '; i++) {
        index++;
    }
    for (int i = 0; i < info->num - my_strlen(str) - m; i++) {
        array[index + i] = '0';
        result++;
    }
    for (int i = 0; info->num < 0 && i < info->zero - my_strlen(str); i++) {
        array[index + i] = '0';
        result++;
    }
    return (result);
}

void identify_char(char *flag, int *i, info_t *info)
{
    int num = (flag[*i] >= '1' && flag[*i] <= '9' ? 0 : 1);
    char arr[2];
    char *tmp = NULL;

    arr[0] = flag[*i];
    arr[1] = '\0';
    identify_format(arr, flag, i, info);
    if (info->zero == -1 && info->num == -2 && num == 0) {
        tmp = my_substr(flag, *i, my_strlen(flag));
        info->zero = my_getnbr(tmp);
        *i = *i + my_nbrlen(info->zero) - 1;
        free(tmp);
    }
    if (info->num == -1 && flag[*i] >= '1' && flag[*i] <= '9') {
        tmp = my_substr(flag, *i, my_strlen(flag));
        info->num = my_getnbr(tmp);
        *i = *i + my_nbrlen(info->num) - 1;
        free(tmp);
    }
}

void identify_format(char *array, char const *flag, int *i, info_t *info)
{
    if (my_str_contains("+#0.", array) == 0) {
        info->plus = (flag[*i] == '+' ? info->plus + 1 : info->plus);
        info->hash = (flag[*i] == '#' ? info->hash + 1 : info->hash);
        info->zero = (info->zero == -2 && flag[*i] == '0' ? -1 : info->zero);
        info->num = (info->num == -2 && flag[*i] == '.' ? -1 : info->num);
    }
}
