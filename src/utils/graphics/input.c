/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Graphical input manager
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include "graphics.h"
#include "my.h"

void insert_key(char key, line_t *line, line_t *buffer)
{
    int gap = line->length - line->pos;
    char *temp = NULL;

    line->length += 1;
    if (line->pos == line->length) {
        line->str[line->pos] = key;
        line->pos += 1;
    } else {
        strncpy(buffer->str, line->str, line->pos);
        strncpy(&buffer->str[line->pos + 1], &line->str[line->pos], gap);
        buffer->str[line->pos] = key;
        buffer->str[line->length] = '\0';
        line->pos += 1;
        temp = buffer->str;
        buffer->str = line->str;
        line->str = temp;
    }
    print_line(line);
}

static void reevaluate_size(line_t *line, line_t *buffer)
{
    if (line->length + 2 == line->size) {
        line->size *= 2;
        line->str = realloc(line->str, line->size);
        buffer->str = realloc(buffer->str, line->size);
    }
}

static bool handle_key(line_t *line, line_t *buffer, shell_t *shell)
{
    int key = buffer->size;

    if (key == '\r' || key == '\n') {
        line->str[line->length] = '\n';
        line->str[line->length + 1] = '\0';
        putchar(key);
        return true;
    }
    if (key == 12) {
        tputs(tgetstr("cl", NULL), 1, putchar);
        print_line(line);
    }
    if (key == 27)
        handle_special_key(line, shell);
    if (key >= 32 && key <= 126)
        insert_key(key, line, buffer);
    if (key == 127)
        backspace(line);
    return (false);
}

char *get_user_input(shell_t *shell)
{
    bool end = false;
    int pressed = 0;
    line_t line = { NULL, BUFFER_SIZE, 0, 0 };
    line_t buffer = { NULL, BUFFER_SIZE, 0, 0 };

    line.str = malloc(sizeof(char) * BUFFER_SIZE);
    buffer.str = malloc(sizeof(char) * BUFFER_SIZE);
    line.str[0] = '\0';
    buffer.str[0] = '\0';
    while (!end) {
        reevaluate_size(&line, &buffer);
        pressed = getc(stdin);
        if (pressed == 4) {
            my_free(2, line.str, buffer.str);
            return (NULL);
        }
        buffer.size = pressed;
        end = handle_key(&line, &buffer, shell);
    }
    free(buffer.str);
    return (line.str);
}
