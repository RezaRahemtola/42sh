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
#include "environment.h"

int start_shell(const char *const *env)
{
    shell_t shell = {0, 0, NULL};
    env_t *list = NULL;
    int ret = 0;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    if (env == NULL) {
        fprintf(stderr, "Error: Invalid environment.\n");
        my_list_free(shell.history, free);
        return (EXIT_USAGE);
    }
    list = get_env_from_array(env);
    remove_env_property(&list, "OLDPWD");
    init_signals();
    do_heartbeat(&list, &shell);
    ret = shell.ret;
    my_list_free(shell.history, free);
    destroy_env(list);
    return (ret);
}

void do_heartbeat(env_t **env, shell_t *shell)
{
    size_t size = 0;
    ssize_t read_size;
    char *line = NULL;

    while (!shell->exit) {
        if (isatty(0))
            printf("$> ");
        read_size = getline(&line, &size, stdin);
        if (read_size == -1)
            shell->exit = true;
        if (read_size > 1) {
            my_list_add(&shell->history, strdup(line));
            handle_input(line, env, shell);
        }
        free(line);
        line = NULL;
    }
    if (isatty(0))
        printf("exit\n");
}
