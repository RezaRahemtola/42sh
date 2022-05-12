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
#include "environment.h"

int start_minishell(char **env)
{
    minishell_t minishell = {0, 0};
    environment_t *list = NULL;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    if (env == NULL) {
        fprintf(stderr, "Error: Invalid environment.\n");
        return (EXIT_USAGE);
    }
    list = get_env_from_array(env);
    remove_env_property(&list, "OLDPWD");
    init_signals();
    do_heartbeat(&list, &minishell);
    destroy_env(list);
    return (minishell.ret);
}

void do_heartbeat(environment_t **env, minishell_t *shell)
{
    size_t size = 0;
    ssize_t read_size;
    char *line = NULL;

    while (shell->exit == 0) {
        if (isatty(0))
            printf("$> ");
        read_size = getline(&line, &size, stdin);
        if (read_size == -1)
            shell->exit = 1;
        if (read_size > 1)
            handle_input(line, env, shell);
        free(line);
        line = NULL;
    }
    if (isatty(0))
        printf("exit\n");
}
