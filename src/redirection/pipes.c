/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Pipe redirections
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

static bool open_redirection(command_t *command)
{
    int fd[2];
    int status = -1;

    if (command->separator_out != PIPE_OUT)
        return (true);
    status = pipe(fd);
    if (status == -1) {
        fprintf(stderr, "%s: %s.\n", command->args[0], strerror(errno));
        return (false);
    }
    command->fd_out = fd[1];
    command->next->fd_in = fd[0];
    return (true);
}

bool open_pipe_redirections(command_t *commands)
{
    command_t *current = commands;

    while (current != NULL) {
        if (!open_redirection(current))
            return (false);
        current = current->next;
    }
    return (true);
}

void handle_pipe_redirections(const command_t *command)
{
    if (command->separator_in == PIPE_IN) {
        dup2(command->fd_in, 0);
        close(command->prev->fd_out);
    }
    if (command->separator_out == PIPE_OUT) {
        dup2(command->fd_out, 1);
        close(command->next->fd_in);
    }
}
