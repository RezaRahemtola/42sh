/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Shell
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"
#include "builtin.h"
#include "history.h"
#include "environment.h"

static void destroy_shell_content(shell_t *shell)
{
    my_list_free(shell->history, free_history);
    destroy_env(shell->aliases);
    destroy_env(shell->env);
    destroy_localenv(shell->localenv);
}

int start_shell(const char *const *env)
{
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    if (env == NULL) {
        fprintf(stderr, "Error: Invalid environment.\n");
        return (EXIT_USAGE);
    }
    shell.env = get_env_from_array(env);
    load_history(&shell);
    load_localenv(&shell);
    remove_env_property(&shell.env, "OLDPWD");
    init_signals();
    do_heartbeat(&shell);
    save_history(shell.history, shell.env);
    destroy_shell_content(&shell);
    return (shell.ret);
}

void do_heartbeat(shell_t *shell)
{
    size_t size = 0;
    ssize_t read_size = 0;
    char *line = NULL;

    while (!shell->exit) {
        if (isatty(0))
            printf("$> ");
        read_size = getline(&line, &size, stdin);
        if (read_size == -1)
            shell->exit = true;
        if (read_size > 1) {
            replace_history(&line, shell);
            handle_input(line, shell);
        }
        free(line);
        line = NULL;
    }
    if (isatty(0))
        printf("exit\n");
}
