/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Startup files
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"
#include "shell.h"

static void execute_rc(FILE *file, shell_t *shell)
{
    ssize_t read = 0;
    size_t size = 0;
    char *line = NULL;

    while (read != -1) {
        read = getline(&line, &size, file);
        if (read > 1 && line[0] != '#')
            handle_input(line, shell);
    }
    free(line);
}

static FILE *load_rc_file(char const *home_path)
{
    size_t home_len = strlen(home_path);
    char *rc_path = malloc(sizeof(char) * (home_len + 9));
    FILE *file = NULL;

    if (rc_path == NULL)
        return (NULL);
    strcpy(rc_path, home_path);
    strcat(rc_path, "/.42shrc");
    file = fopen(rc_path, "r");
    free(rc_path);
    return (file);
}

void load_rc(shell_t *shell)
{
    const env_t *home = get_env_value(shell->env, "HOME");
    FILE *rc_file = NULL;

    if (home == NULL)
        return;
    rc_file = load_rc_file(home->value);
    if (rc_file == NULL)
        return;
    execute_rc(rc_file, shell);
    fclose(rc_file);
}
