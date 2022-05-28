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

static void init_shell(shell_t *shell, const char *const *env)
{
    shell->env = get_env_from_array(env);
    load_history(shell);
    load_localenv(shell);
    remove_env_property(&shell->env, "OLDPWD");
}

static void terminate_shell(shell_t *shell)
{
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

static void handle_eof(shell_t *shell)
{
    const localenv_t *ignore = get_localenv_value(shell->localenv, "ignoreeof");

    clearerr(stdin);
    if (ignore == NULL) {
        shell->exit = true;
        return;
    }
    if (strlen(ignore->value) == 0 || strcmp(ignore->value, "0") == 0)
        printf("Use \"exit\" to leave 42sh.\n");
}

void do_heartbeat(shell_t *shell, const char *const *env)
{
    size_t size = 0;
    ssize_t read_size = 0;
    char *line = NULL;

    init_shell(shell, env);
    while (!shell->exit) {
        display_prompt();
        read_size = getline(&line, &size, stdin);
        if (read_size == -1)
            handle_eof(shell);
        if (read_size > 1) {
            replace_history(&line, shell);
            handle_input(line, shell);
        }
        free(line);
        line = NULL;
    }
    if (isatty(0))
        printf("exit\n");
    terminate_shell(shell);
}
