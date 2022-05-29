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
const char *pwd)
{
    return malloc(sizeof(char) * (strlen("[@ ]$ ") +
                                  strlen(login) + strlen(hostname) +
                                  strlen(pwd) + 1));
}

static void destoy_prompt_elements(char *error_prompt, char *pwd)
{
    free(error_prompt);
    free(pwd);
}

static char *get_pwd(char *login)
{
    char *cwd = getcwd(NULL, 0);
    char *home_dir = malloc(sizeof(char) *
                            (strlen("/home/") + strlen(login) + 1));
    char *result = NULL;

    sprintf(home_dir, "/home/%s", login);
    if (strcmp(home_dir, cwd) != 0)
        result = strdup(strrchr(cwd, '/') + 1);
    else
        result = strdup("~");
    free(cwd);
    free(home_dir);
    return result;
}

char *get_prompt(void)
{
    char hostname[HOST_NAME_MAX + 1];
    char *error_prompt = strdup("? $ ");
    char *prompt = NULL;
    char *login = getlogin();
    char *pwd = NULL;

    if (!login || gethostname(hostname, HOST_NAME_MAX + 1) < 0)
        return error_prompt;
    pwd = get_pwd(login);
    if (!pwd)
        return error_prompt;
    prompt = allocate_prompt(login, hostname, pwd);
    sprintf(prompt, "[%s@%s %s]$ ", login, hostname, pwd);
    destoy_prompt_elements(error_prompt, pwd);
    return (prompt);
}
