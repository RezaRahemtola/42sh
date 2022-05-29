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

void execute_line(const char *line, shell_t *shell)
{
    char *fixed = NULL;
    size_t size = strlen(line);

    if (line[size - 1] == '\n') {
        handle_input(line, shell);
    } else {
        fixed = malloc(sizeof(char) * (size + 2));
        sprintf(fixed, "%s\n", line);
        handle_input(fixed, shell);
        free(fixed);
    }
}

static void execute_rc(FILE *file, shell_t *shell)
{
    ssize_t read = 0;
    size_t size = 0;
    char *line = NULL;

    while (read != -1) {
        read = getline(&line, &size, file);
        if (read > 1 && line[0] != '#')
            execute_line(line, shell);
    }
    free(line);
}

static FILE *load_rc_file(const char *home_path)
{
    size_t home_len = strlen(home_path);
    char *rc_path = malloc(sizeof(char) * (home_len + 9));
    FILE *file = NULL;

    if (rc_path == NULL)
        return (NULL);
    sprintf(rc_path, "%s/.42shrc", home_path);
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
