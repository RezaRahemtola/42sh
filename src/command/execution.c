/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Command execution
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtin.h"
#include "jobs.h"
#include "logical.h"
#include "shell.h"

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

static void wait_commands(command_t *cmd, shell_t *shell)
{
    int status = 0;
    command_t *current = cmd;

    while (current != NULL && current->state == RUNNING && !cmd->job_check) {
        waitpid(current->pid, &status, WUNTRACED | WCONTINUED);
        handle_errors(status);
        if (!is_builtin(current->args[0]) && !must_relay_status(current)) {
            current->ret = (status > 255 ? status / 256 : status);
            shell->ret = current->ret;
        }
        current = current->next;
    }
}

static pid_t execute_single(command_t *command, shell_t *shell)
{
    pid_t pid = 0;

    replace_aliases(command, shell->aliases, shell->env);
    replace_variables(command, shell);
    if (command->state == ABORTED)
        return (0);
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "%s: %s.\n", command->args[0], strerror(errno));
        return (-1);
    } else if (pid == 0) {
        execute_forked(command, shell);
        exit(!is_command_empty(command));
    }
    if (command->fd_out != 0)
        close(command->fd_out);
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
        current->state = (pid > 0 ? RUNNING : current->state);
        if (current->state == ABORTED) {
            return list_size(cmd);
        }
        total++;
        current = current->next;
    } while (current != NULL && current->separator_in == PIPE_IN);
    if (cmd->job_check)
        shell->job = add_job_pid(shell->job, cmd->input, pid, shell->nb_job);
    wait_commands(cmd, shell);
    return (total);
}

void execute_commands(command_t *command, shell_t *shell)
{
    size_t executed_number = 0;
    command_t *current = command;
    job_t *new = NULL;

    while (current != NULL) {
        if (job_command_case(current->input)) {
            current->args = remove_incorrect_char(current->args);
            new = malloc(sizeof(job_t));
            new->command = strdup(current->input);
            shell->nb_job++;
            new->nb_job = shell->nb_job;
            my_list_add(&shell->job, new);
            current->job_check = true;
        }
        executed_number = execute_command_line(current, shell);
        for (size_t i = 0; i < executed_number && current != NULL; i++)
            current = current->next;
    }
}
