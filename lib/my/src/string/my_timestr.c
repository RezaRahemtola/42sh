/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Function to get a string of the current time
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

char *my_timestr(void)
{
    time_t current_time = time(NULL);
    struct tm *now= localtime(&current_time);
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
