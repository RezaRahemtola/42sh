/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history substitutions
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "messages.h"
#include "my_math.h"
#include "my_string.h"

void handle_last_substitution(char **input, list_t *history)
{
    char *new = NULL;

    if (my_list_size(history) == 0) {
        fprintf(stderr, "0: %s\n", NO_EVENT);
        free(*input);
        *input = NULL;
    } else {
        new = my_strrep(*input, "!!", get_history_command(history, -1));
        free(*input);
        *input = new;
    }
}

void handle_nb_substitution(char **input, char *current, list_t *history)
{
    int nb = atoi(current);
    char *cmd = get_history_command(history, nb);
    char *pattern = NULL;
    char *new = NULL;

    if (cmd == NULL) {
        fprintf(stderr, "%d: %s\n", nb, NO_EVENT);
        free(*input);
        *input = NULL;
    } else {
        pattern = malloc(sizeof(char) * (my_nbrlen(nb) + 2));
        sprintf(pattern, "!%d", nb);
        new = my_strrep(*input, pattern, cmd);
        free(*input);
        *input = new;
        free(pattern);
    }
}

void handle_str_substitution(char **input, char *current, list_t *history)
{
    char *pattern = malloc(sizeof(char) * strlen(current) + 2);
    char *cmd = NULL;
    char *new = NULL;

    pattern[0] = '!';
    for (size_t i = 0; isalpha(current[i]); i++) {
        pattern[i + 1] = current[i];
        pattern[i + 2] = '\0';
    }
    cmd = get_history_by_str(history, &pattern[1]);
    if (cmd == NULL) {
        fprintf(stderr, "%s: %s\n", &pattern[1], NO_EVENT);
        free(*input);
        *input = NULL;
    } else {
        new = my_strrep(*input, pattern, cmd);
        free(*input);
        *input = new;
    }
    free(pattern);
}
