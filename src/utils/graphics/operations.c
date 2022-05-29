/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Buffer operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

void move_cursor(int delta, line_t *line)
{
    int new = line->pos + delta;
    if (new >= 0 && new <= line->length)
        line->pos = new;
}

void backspace(line_t *line)
{
    int gap = line->length - line->pos;

    if (line->length == 0)
        return;
    if (line->pos != 0) {
        strncpy(&line->str[line->pos - 1], &line->str[line->pos], gap);
        line->pos -= 1;
        line->length -= 1;
        line->str[line->length] = '\0';
    }
    print_line(line);
}

void suppr(line_t *line)
{
    int gap = line->length - line->pos;

    if (line->pos != line->length) {
        strncpy(&line->str[line->pos], &line->str[line->pos + 1], gap);
        line->length -= 1;
    }
}

void print_line(line_t *line)
{
    char *prompt = get_prompt();

    printf("\33[2K\r");
    printf("%s%s", prompt, line->str);
    if (line->pos < line->length)
        printf("\033[%dD", line->length - line->pos);
    free(prompt);
}
