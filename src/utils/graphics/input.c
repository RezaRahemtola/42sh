/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Graphical input manager
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include "my.h"

void insert_key(char key, line_t *line, line_t *buffer)
{
    char *temp = NULL;

    line->length += 1;
    if (line->pos == line->length) {
        line->str[line->pos] = key;
        line->pos += 1;
    } else {
        strncpy(buffer->str, line->str, line->pos);
        strncpy(&buffer->str[line->pos + 1], &line->str[line->pos], line->length - line->pos);
        buffer->str[line->pos] = key;
        buffer->str[line->length] = '\0';
        line->pos += 1;
        temp = buffer->str;
        buffer->str = line->str;
        line->str = temp;
    }
    printf("\33[2K\r");
    printf("$> %s", line->str);
    if (line->pos < line->length)
        printf("\033[%dD", line->length - line->pos);
}

static void move_cursor(int delta, line_t *line)
{
    int new = line->pos + delta;
    if (new >= 0 && new <= line->length)
        line->pos = new;
}

static void backspace(line_t *line) {
    if (line->length == 0)
        return;
    if (line->pos != 0) {
        strncpy(&line->str[line->pos - 1], &line->str[line->pos], line->length - line->pos);
        line->pos -= 1;
        line->length -= 1;
        line->str[line->length] = '\0';
    }
    printf("\33[2K\r");
    printf("$> %s", line->str);
    if (line->pos < line->length)
        printf("\033[%dD", line->length - line->pos);
}

static void suppr(line_t *line) {
    if (line->pos != line->length) {
        strncpy(&line->str[line->pos], &line->str[line->pos + 1], line->length - line->pos);
        line->length -= 1;
    }
}

static void reevaluate_size(line_t *line, line_t *buffer)
{
    if (line->length + 2 == line->size) {
        line->size *= 2;
        line->str = realloc(line->str, line->size);
        buffer->str = realloc(buffer->str, line->size);
    }
}

static void handle_special_key(line_t *line)
{
    int second = getchar();
    int third = 0;

    if (second != 91)
        return;
    third = getchar();
    switch (third) {
        case 65:
            printf("up arrow key pressed\n");
            break;
        case 66:
            printf("down arrow key pressed\n");
            break;
        case 67:
            if (line->pos == line->length)
                break;
            printf("\033[1C");
            move_cursor(1, line);
            break;
        case 68:
            if (line->pos == 0)
                break;
            printf("\033[1D");
            move_cursor(-1, line);
            break;
    }
}

static bool handle_key_pressed(int key, line_t *line, line_t *buffer)
{
    if (key == '\r' || key == '\n') {
        line->str[line->length] = '\n';
        line->str[line->length + 1] = '\0';
        putchar(key);
        return true;
    }
    if (key == 12)
        system("clear");
    if (key == 27)
        handle_special_key(line);
    if (key >= 32 && key <= 126)
        insert_key(key, line, buffer);
    if (key == 127)
        backspace(line);
    return (false);
}

char *get_user_input(void)
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
        end = handle_key_pressed(pressed, &line, &buffer);
    }
    free(buffer.str);
    return (line.str);
}