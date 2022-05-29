/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to display the prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "environment.h"
#include "shell.h"

void exec_special_alias(const char *key, shell_t *shell)
{
    const env_t *alias = get_env_value(shell->aliases, key);

    if (alias != NULL)
        execute_line(alias->value, shell);
}

static char *allocate_prompt(const char *login, const char *hostname,
    const char *current_dir_name)
{
    return malloc(sizeof(char) * (strlen("[@ ]$ ") +
                                  strlen(login) + strlen(hostname) +
                                  strlen(current_dir_name) + 1));
}

static void destoy_prompt_elements(char *cwd, char *error_prompt,
    char *current_dir_name)
{
    free(cwd);
    free(error_prompt);
    free(current_dir_name);
}

char *get_prompt(void)
{
    char hostname[HOST_NAME_MAX + 1];
    char *error_prompt = strdup("? $ ");
    char *prompt;
    char *cwd = getcwd(NULL, 0);
    char *login = getlogin();
    char *current_dir_name;

    if (!cwd || !login || gethostname(hostname, HOST_NAME_MAX + 1) < 0)
        return error_prompt;
    current_dir_name = strdup(strrchr(cwd, '/') + 1);
    if (!current_dir_name)
        return error_prompt;
    prompt = allocate_prompt(login, hostname, current_dir_name);
    sprintf(prompt, "[%s@%s %s]$ ", login, hostname, current_dir_name);
    destoy_prompt_elements(cwd, error_prompt, current_dir_name);
    return (prompt);
}
