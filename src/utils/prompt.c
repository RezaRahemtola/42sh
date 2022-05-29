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

static void exec_precmd_alias(shell_t *shell)
{
    const env_t *precmd = get_env_value(shell->aliases, "precmd");

    if (precmd != NULL)
        execute_line(precmd->value, shell);
}

void prompt(shell_t *shell)
{
    exec_precmd_alias(shell);
    if (isatty(0))
        printf("$> ");
}
