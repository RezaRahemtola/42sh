/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Shell
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "environment.h"
#include "history.h"
#include "messages.h"
#include "shell.h"

static void init_shell(shell_t *shell, const char *const *env)
{
    shell->env = get_env_from_array(env);
    load_history(shell);
    load_localenv(shell);
    remove_env_property(&shell->env, "OLDPWD");
}

static void terminate_shell(shell_t *shell)
{
    if (isatty(0))
        printf("exit\n");
    save_history(shell->history, shell->env);
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
    init_signals();
    do_heartbeat(&shell, env);
    return (shell.ret);
}

static void handle_eof(shell_t *shell, int nb_eof)
{
    const localenv_t *var = get_localenv_value(shell->localenv, "ignoreeof");
    bool empty = false;
    int value = 0;

    clearerr(stdin);
    if (var == NULL) {
        shell->exit = true;
        return;
    }
    empty = (strlen(var->value) == 0 || strcmp(var->value, "0") == 0);
    value = atoi(var->value);
    if (empty || (isdigit(var->value[0]) && nb_eof < value))
        printf("^D\n%s\n", IGNOREEOF_MESSAGE);
    else if (nb_eof == value)
        shell->exit = true;
}

void do_heartbeat(shell_t *shell, const char *const *env)
{
    size_t size = 0;
    ssize_t read_size = 0;
    char *line = NULL;
    int nb_eof = 0;

    init_shell(shell, env);
    while (!shell->exit) {
        display_prompt();
        read_size = getline(&line, &size, stdin);
        nb_eof = (read_size == -1 ? nb_eof + 1 : 0);
        if (read_size == -1)
            handle_eof(shell, nb_eof);
        if (read_size > 1) {
            replace_history(&line, shell);
            handle_input(line, shell);
        }
        free(line);
        line = NULL;
    }
    terminate_shell(shell);
}
