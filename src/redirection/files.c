/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** File redirections
*/

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my_string.h"

static int write_input_redir(const char *str, const char *cmd_name)
{
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        fprintf(stderr, "%s: %s.\n", cmd_name, strerror(errno));
        return (-1);
    }
    write(pipefd[1], str, strlen(str));
    close(pipefd[1]);
    return (pipefd[0]);
}

static int read_input_redir(const command_t *command)
{
    char *result = strdup("\0");
    char *content = NULL;
    size_t size = 0;
    ssize_t read = 0;

    while (true) {
        printf("? ");
        read = getline(&content, &size, stdin);
        if (read == -1 || strcmp(content, command->info_in) == '\n')
            break;
        result = realloc(result, sizeof(char) * (strlen(result) + read + 1));
        strcat(result, content);
        free(content);
        content = NULL;
    }
    return (write_input_redir(result, command->args[0]));
}

bool open_input_redirection(command_t *command)
{
    separator_in_type_t separator = command->separator_in;

    if (separator != FILE_READ && separator != INPUT_READ)
        return (true);
    if (separator == INPUT_READ)
        command->fd_in = read_input_redir(command);
    else
        command->fd_in = open(command->info_in, O_RDONLY);
    if (command->fd_in == -1) {
        fprintf(stderr, "%s: %s.\n", command->info_in, strerror(errno));
        return (false);
    }
    dup2(command->fd_in, 0);
    return (true);
}

bool open_output_redirection(command_t *command)
{
    int flags = 0;
    separator_out_type_t separator = command->separator_out;

    if (separator != FILE_WRITE && separator != FILE_APPEND)
        return (true);
    if (separator == FILE_WRITE)
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    else
        flags = O_CREAT | O_WRONLY | O_APPEND;
    command->fd_out = open(command->info_out, flags, 0664);
    if (command->fd_out == -1) {
        fprintf(stderr, "%s: %s.\n", command->info_out, strerror(errno));
        return (false);
    }
    dup2(command->fd_out, 1);
    return (true);
}

void close_redirections(const command_t *command)
{
    if (command->fd_in != 0)
        close(command->fd_in);
    if (command->fd_out != 0)
        close(command->fd_out);
}
