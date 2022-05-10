/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Command execution
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtin.h"
#include "minishell.h"
#include "my_string.h"
#include "my.h"
#include "redirections.h"

static void execute_silent(command_t *command, varenv_t **env, \
minishell_t *shell)
{
    if (is_command_empty(command)) {
        return;
    }
    for (int i = 0; BUILTIN[i].command != NULL; i++) {
        if (my_strcmp(command->args[0], BUILTIN[i].command) == 0) {
            BUILTIN[i].silent(env, command->args, shell);
            return;
        }
    }
}

static void wait_commands(pidlist_t *pidlist, minishell_t *shell)
{
    int status = 0;
    pidlist_t *current = pidlist;

    while (current != NULL) {
        waitpid(current->pid, &status, WUNTRACED | WCONTINUED);
        handle_errors(status);
        shell->ret = (status > 255 ? status / 256 : status);
        current = current->next;
    }
}

static pid_t execute_single(command_t *command, varenv_t **env, \
minishell_t *shell)
{
    pid_t pid = fork();

    if (pid == -1) {
        my_dprintf(2, "%s: %s.\n", command->args[0], strerror(errno));
        return (-1);
    } else if (pid == 0) {
        execute_forked(command, env);
        exit(!is_command_empty(command) && !is_builtin(command->args[0]));
    }
    execute_silent(command, env, shell);
    return (pid);
}

static int execute_command_line(command_t *command, varenv_t **env, \
minishell_t *shell)
{
    int total = 0;
    pid_t pid = 0;
    pidlist_t *pids = NULL;
    command_t *current = command;

    do {
        pid = execute_single(current, env, shell);
        if (pid > 0) {
            pidlist_append(&pids, create_pidlist(pid));
        }
        total++;
        close_output_redirection(current);
        current = current->next;
    } while (current != NULL && current->separator_in == PIPE_IN);
    wait_commands(pids, shell);
    pidlist_free(pids);
    return (total);
}

void execute_commands(command_t *command, varenv_t **env, minishell_t *shell)
{
    int number = 0;
    command_t *current = command;

    while (current != NULL) {
        number = execute_command_line(current, env, shell);
        for (int i = 0; i < number && current != NULL; i++) {
            current = current->next;
        }
    }
}
