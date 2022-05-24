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

static void make_history_substitutions(char **input, list_t *history)
{
    char *new = strchr(*input, '!');

    while (new != NULL && *input != NULL) {
        if (isdigit(new[1]))
            handle_nb_substitution(input, &new[1], history);
        if (isalpha(new[1]))
            handle_str_substitution(input, &new[1], history);
        new = strchr(++new, '!');
    }
}

void replace_history(char **input, shell_t *shell)
{
    char *old = strdup(*input);

    if (strstr(*input, "!!") != NULL)
        handle_last_substitution(input, shell->history);
    if (*input != NULL && strchr(*input, '!') != NULL)
        make_history_substitutions(input, shell->history);
    if (*input != NULL && strcmp(*input, old) != 0)
        printf("%s", *input);
    if (*input != NULL)
        add_history(*input, shell);
    else
        *input = strdup(" ");
    free(old);
}
