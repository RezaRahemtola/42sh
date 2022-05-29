/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to display the prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "environment.h"
#include "shell.h"

void exec_special_alias(const char *key, shell_t *shell)
{
    const env_t *alias = get_env_value(shell->aliases, key);

    if (alias != NULL)
        execute_line(alias->value, shell);
}

char *get_prompt(void)
{
    char *prompt = malloc(sizeof(char) * 4);

    sprintf(prompt, "$> ");
    return (prompt);
}
