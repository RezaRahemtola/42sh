/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Arrows handling
*/

#include <stdio.h>
#include "graphics.h"

void arrow_up(line_t *line)
{
    (void) line;
}

void arrow_down(line_t *line)
{
    (void) line;
}

void arrow_left(line_t *line)
{
    if (line->pos != line->length) {
        printf("\033[1C");
        move_cursor(1, line);
    }
}

void arrow_right(line_t *line)
{
    if (line->pos != 0) {
        printf("\033[1D");
        move_cursor(-1, line);
    }
}

void handle_special_key(line_t *line)
{
    int second = getchar();
    int third = 0;

    if (second != 91)
        return;
    third = getchar();
    for (int i = 0; i < 4; i++) {
        if (third == 65 + i) {
            ARROW_HANDLERS[i](line);
        }
    }
}
