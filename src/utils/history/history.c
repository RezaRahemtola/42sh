/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "my_string.h"
#include "my_math.h"

static void replace_last_command(char **input, list_t *history)
{
    char *new = NULL;

    if (my_list_size(history) == 0) {
        dprintf(2, "0: Event not found.\n");
        free(*input);
        *input = NULL;
    } else {
        new = my_strrep(*input, "!!", get_history_command(history, -1));
        free(*input);
        *input = new;
    }
}

static void handle_nb_substitution(char **input, char *current, list_t *history)
{
    int nb = atoi(current);
    char *cmd = get_history_command(history, nb);
    char *pattern = NULL;
    char *new = NULL;

    if (cmd == NULL) {
        dprintf(2, "%d: Event not found.\n", nb);
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

static void make_history_substitutions(char **input, list_t *history)
{
    char *new = strchr(*input, '!');

    while (new != NULL && *input != NULL) {
        if (isdigit(new[1]))
            handle_nb_substitution(input, &new[1], history);
        new = strchr(++new, '!');
    }
}

void replace_history(char **input, shell_t *shell)
{
    char *old = strdup(*input);

    if (strstr(*input, "!!") != NULL)
        replace_last_command(input, shell->history);
    if (strchr(*input, '!') != NULL)
        make_history_substitutions(input, shell->history);
    if (strcmp(*input, old) != 0)
        printf("%s", *input);
    if (*input != NULL)
        add_history(*input, shell);
    else
        *input = strdup(" ");
    free(old);
}
