/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Command executor
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"
#include "shell.h"
#include "messages.h"
#include "redirections.h"
#include "environment.h"

static void execute_builtin(command_t *command, env_t **env)
{
    for (size_t i = 0; BUILTIN[i].command != NULL; i++)
        if (strcmp(command->args[0], BUILTIN[i].command) == 0) {
            BUILTIN[i].function(env, command->args);
            return;
        }
}

static void execute_binary(command_t *command, env_t **env)
{
    char **environment_array = get_array_from_env(*env);

    if (environment_array == NULL)
        return;
    execve(command->path, command->args, environment_array);
    if (errno == ENOEXEC)
        fprintf(stderr, "%s: %s\n", command->args[0], WRONG_ARCH);
    else
        fprintf(stderr, "%s: %s.\n", command->args[0], strerror(errno));
}

void execute_forked(command_t *cmd, env_t **env)
{
    bool builtin = is_builtin(cmd->args[0]);

    init_signals();
    handle_pipe_redirections(cmd);
    if (!open_input_redirection(cmd) || !open_output_redirection(cmd) ||
        is_command_empty(cmd) || is_directory(cmd->path))
        return;
    if (cmd->path == NULL && !builtin) {
        fprintf(stderr, "%s: Command not found.\n", cmd->args[0]);
        return;
    }
    if (builtin)
        execute_builtin(cmd, env);
    else
        execute_binary(cmd, env);
    close_input_redirection(cmd);
    close_output_redirection(cmd);
}
