/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Graphical input manager
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

static void reevaluate_size(size_t in, size_t *size, char **line)
{
    if (in + 3 == *size) {
        *size *= 2;
        *line = realloc(*line, *size);
    }
}

static void handle_special_key(void)
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
            printf("right arrow key pressed\n");
            break;
        case 68:
            printf("left arrow key pressed\n");
            break;
    }
}

static bool handle_key_pressed(int key, char *line, size_t *in)
{
    if (key == '\r' || key == '\n') {
        line[*in] = '\n';
        line[*in + 1] = '\0';
        putchar(key);
        return true;
    }
    if (key == 12)
        system("clear");
    if (key == 27)
        handle_special_key();
    if (key >= 32 && key <= 126) {
        putchar(key);
        line[*in] = key;
        *in += 1;
    }
    return (false);
}

char *get_user_input(void)
{
    bool end = false;
    int pressed = 0;
    size_t in = 0;
    size_t size = BUFFER_SIZE;
    char *line = malloc(sizeof(char) * BUFFER_SIZE);

    while (!end) {
        reevaluate_size(in, &size, &line);
        pressed = getc(stdin);
        if (pressed == 4) {
            free(line);
            return (NULL);
        }
        end = handle_key_pressed(pressed, line, &in);
    }
    return (line);
}

