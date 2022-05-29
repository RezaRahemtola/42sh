/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to display the prompt
*/

#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include "environment.h"

void exec_special_alias(const char *key, shell_t *shell)
{
    const env_t *alias = get_env_value(shell->aliases, key);

    if (alias != NULL)
        execute_line(alias->value, shell);
}

void prompt(shell_t *shell)
{
    exec_special_alias("precmd", shell);
    if (shell->graphical)
        printf("$> ");
}
