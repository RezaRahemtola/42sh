/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Function to get a string of the current time
*/

#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *my_timestr(void)
{
    time_t current_time = time(NULL);
    struct tm *now = localtime(&current_time);
    char *result = malloc(sizeof(char) * 6);

    if (now->tm_hour < 10 && now->tm_min < 10) {
        sprintf(result, "0%d:0%d", now->tm_hour, now->tm_min);
    } else {
        if (now->tm_hour < 10)
            sprintf(result, "0%d:%d", now->tm_hour, now->tm_min);
        if (now->tm_min < 10)
            sprintf(result, "%d:0%d", now->tm_hour, now->tm_min);
        if (now->tm_hour >= 10 && now->tm_min >= 10)
            sprintf(result, "%d:%d", now->tm_hour, now->tm_min);
    }
    return (result);
}

bool my_isalphanum_str(const char *str)
{
    size_t size = strlen(str);

    for (size_t i = 0; i < size; i++)
        if (!isalnum(str[i]))
            return (false);
    return (true);
}

bool my_isalpha_str(const char *str)
{
    size_t size = strlen(str);

    for (size_t i = 0; i < size; i++)
        if (!isalpha(str[i]))
            return (false);
    return (true);
}
