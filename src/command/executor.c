/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Command executor
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"
#include "minishell.h"
#include "my.h"
#include "messages.h"
#include "redirections.h"
#include "varenv.h"
#include "my_string.h"

static void execute_builtin(command_t *command, varenv_t **env)
{
    for (int i = 0; BUILTIN[i].command != NULL; i++) {
        if (my_strcmp(command->args[0], BUILTIN[i].command) == 0) {
            BUILTIN[i].function(env, command->args);
            return;
        }
    }
}

static void execute_binary(command_t *command, varenv_t **env)
{
    char **array = convert_varenv(*env);

    if (array == NULL) {
        return;
    }
    execve(command->path, command->args, array);
    if (errno == ENOEXEC) {
        fprintf(stderr, "%s: %s\n", command->args[0], WRONG_ARCH);
    } else {
        fprintf(stderr, "%s: %s.\n", command->args[0], strerror(errno));
    }
}

void execute_forked(command_t *cmd, varenv_t **env)
{
    bool builtin = is_builtin(cmd->args[0]);

    init_signals();
    handle_pipe_redirections(cmd);
    if (!open_input_redirection(cmd) || !open_output_redirection(cmd)) {
        return;
    } else if (is_command_empty(cmd) || check_directory(cmd->path)) {
        return;
    }
    if (cmd->path == NULL && !builtin) {
        my_dprintf(2, "%s: Command not found.\n", cmd->args[0]);
        return;
    }
    if (builtin) {
        execute_builtin(cmd, env);
    } else {
        execute_binary(cmd, env);
    }
    close_input_redirection(cmd);
    close_output_redirection(cmd);
}
