/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history substitutions
*/

#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "my_string.h"
#include "my_math.h"

void handle_last_substitution(char **input, list_t *history)
{
    char *new = NULL;

    if (my_list_size(history) == 0) {
        fprintf(stderr, "0: Event not found.\n");
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
        fprintf(stderr, "%d: Event not found.\n", nb);
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
    (void)input;
    (void)current;
    (void)history;
    return;
}
