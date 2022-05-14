/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Command execution
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "builtin.h"
#include "shell.h"
#include "redirections.h"

static void execute_silent(command_t *command, env_t **env, shell_t *shell)
{
    if (is_command_empty(command))
        return;
    for (size_t i = 0; BUILTIN[i].command != NULL; i++)
        if (strcmp(command->args[0], BUILTIN[i].command) == 0) {
            command->ret = BUILTIN[i].silent_function(env, command->args,
                shell);
            return;
        }
}

static void wait_commands(command_t *command, shell_t *shell)
{
    int status = 0;
    command_t *current = command;

    while (current != NULL && current->state == RUNNING) {
        waitpid(current->pid, &status, WUNTRACED | WCONTINUED);
        handle_errors(status);
        shell->ret = (status > 255 ? status / 256 : status);
        if (command->ret != -1)
            shell->ret = command->ret;
        current = current->next;
    }
}

static pid_t execute_single(command_t *command, env_t **env, shell_t *shell)
{
    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "%s: %s.\n", command->args[0], strerror(errno));
        return (-1);
    } else if (pid == 0) {
        execute_forked(command, env);
        exit(!is_command_empty(command));
    }
    execute_silent(command, env, shell);
    return (pid);
}

static int execute_command_line(command_t *command, env_t **env, shell_t *shell)
{
    int total_executed = 0;
    pid_t pid = 0;
    command_t *current = command;

    do {
        pid = execute_single(current, env, shell);
        if (pid > 0) {
            command->pid = pid;
            command->state = RUNNING;
        }
        total_executed++;
        close_redirections(current);
        current = current->next;
    } while (current != NULL && current->separator_in == PIPE_IN);
    wait_commands(command, shell);
    return (total_executed);
}

void execute_commands(command_t *command, env_t **env, shell_t *shell)
{
    size_t executed_number = 0;
    command_t *current = command;

    while (current != NULL) {
        executed_number = execute_command_line(current, env, shell);
        for (size_t i = 0; i < executed_number && current != NULL; i++)
            current = current->next;
    }
}
