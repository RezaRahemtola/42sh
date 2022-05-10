/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Minishell
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "varenv.h"

int minishell(int argc, char **argv, char **env)
{
    minishell_t minishell = { 0, 0 };
    varenv_t *list = NULL;

    (void) argc;
    (void) argv;
    if (env == NULL) {
        fprintf(stderr, "Error: Invalid environment.\n");
        return (EXIT_USAGE);
    }
    list = convert_env(env);
    varenv_remove(&list, "OLDPWD");
    init_signals();
    shell_heartbeat(&list, &minishell);
    destroy_env(list);
    return (minishell.ret);
}

void shell_heartbeat(varenv_t **env, minishell_t *shell)
{
    size_t size = 0;
    char *line = NULL;

    while (shell->exit == 0) {
        if (isatty(0)) {
            printf("$> ");
        }
        size = getline(&line, &size, stdin);
        if ((int) size == -1) {
            shell->exit = 1;
        }
        if ((int) size > 1) {
            handle_input(line, env, shell);
        }
        free(line);
        line = NULL;
    }
    if (isatty(0)) {
        printf("exit\n");
    }
}
