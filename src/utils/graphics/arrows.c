/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Arrows handling
*/

#include <stdio.h>
#include "graphics.h"
#include "history.h"

void arrow_up(line_t *line, int *count, shell_t *shell)
{
    history_t *prev = NULL;

    *count -= 1;
    prev = get_history(shell->history, *count);
    if (prev == NULL) {
        *count += 1;
        return;
    }
    set_line(line, prev->command);
}

void arrow_down(line_t *line, int *count, shell_t *shell)
{
    history_t *next = NULL;

    *count += 1;
    if (*count > 0) {
        *count = 0;
        return;
    }
    if (*count == 0) {
        set_line(line, "");
    }
    next = get_history(shell->history, *count);
    if (next == NULL) {
        *count -= 1;
        return;
    }
    set_line(line, next->command);
}

void arrow_left(line_t *line, int *count, shell_t *shell)
{
    (void) count;
    (void) shell;
    if (line->pos != line->length) {
        printf("\033[1C");
        move_cursor(1, line);
    }
}

void arrow_right(line_t *line, int *count, shell_t *shell)
{
    (void) count;
    (void) shell;
    if (line->pos != 0) {
        printf("\033[1D");
        move_cursor(-1, line);
    }
}

void handle_special_key(line_t *line, int *count, shell_t *shell)
{
    int second = getchar();
    int third = 0;

    if (second != 91)
        return;
    third = getchar();
    for (int i = 0; i < 4; i++) {
        if (third == 65 + i) {
            ARROW_HANDLERS[i](line, count, shell);
        }
    }
}
