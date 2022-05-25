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
#include "logical.h"
#include "shell.h"
#include "redirections.h"

static void execute_silent(command_t *command, shell_t *shell)
{
    if (is_command_empty(command))
        return;
    for (size_t i = 0; BUILTIN[i].command != NULL; i++)
        if (strcmp(command->args[0], BUILTIN[i].command) == 0) {
            command->ret = BUILTIN[i].silent_function(shell, command->args);
            shell->ret = command->ret;
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
        current->ret = (status > 255 ? status / 256 : status);
        if (!is_builtin(current->args[0]))
            shell->ret = current->ret;
        current = current->next;
    }
}

static pid_t execute_single(command_t *command, shell_t *shell)
{
    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "%s: %s.\n", command->args[0], strerror(errno));
        return (-1);
    } else if (pid == 0) {
        execute_forked(command, shell);
        exit(!is_command_empty(command));
    }
    execute_silent(command, shell);
    return (pid);
}

static size_t execute_command_line(command_t *cmd, shell_t *shell)
{
    size_t total = 0;
    pid_t pid = 0;
    command_t *current = cmd;

    if (should_ignore(cmd))
        return (ignore_command(cmd));
    do {
        pid = execute_single(current, shell);
        current->pid = (pid > 0 ? pid : 0);
        current->state = (pid > 0 ? RUNNING : IDLE);
        total++;
        close_redirections(current);
        current = current->next;
    } while (current != NULL && current->separator_in == PIPE_IN);
    wait_commands(cmd, shell);
    return (total);
}

void execute_commands(command_t *command, shell_t *shell)
{
    size_t executed_number = 0;
    command_t *current = command;

    while (current != NULL) {
        executed_number = execute_command_line(current, shell);
        for (size_t i = 0; i < executed_number && current != NULL; i++)
            current = current->next;
    }
}
