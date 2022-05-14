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

static int read_input(command_t *command)
{
    char *result = strdup("\0");
    char *content = NULL;
    size_t size = 0;
    ssize_t read_size = 0;
    int pipefd[2];

    while (true) {
        printf("? ");
        read_size = getline(&content, &size, stdin);
        if (read_size == -1 || strcmp(content, command->info_in) == '\n')
            break;
        result = realloc(result, sizeof(char) * (strlen(result) + read_size + 1));
        strcat(result, content);
        free(content);
        content = NULL;
    }
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "%s: %s.\n", command->args[0], strerror(errno));
        return (-1);
    }
    write(pipefd[1], result, strlen(result));
    close(pipefd[1]);
    return (pipefd[0]);
}

bool open_input_redirection(command_t *command)
{
    int fd = -1;
    separator_in_type_t separator = command->separator_in;

    if (separator != FILE_READ && separator != INPUT_READ)
        return (true);
    if (separator == INPUT_READ)
        fd = read_input(command);
    else
        fd = open(command->info_in, O_RDONLY);
    command->fd_in = fd;
    if (fd == -1) {
        fprintf(stderr, "%s: %s.\n", command->info_in, strerror(errno));
        return (false);
    }
    dup2(command->fd_in, 0);
    return (true);
}

bool open_output_redirection(command_t *command)
{
    int fd = -1;
    int flags = 0;
    separator_out_type_t separator = command->separator_out;

    if (separator != FILE_WRITE && separator != FILE_APPEND)
        return (true);
    if (separator == FILE_WRITE)
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    else
        flags = O_CREAT | O_WRONLY | O_APPEND;
    fd = open(command->info_out, flags, 0664);
    if (fd == -1) {
        fprintf(stderr, "%s: %s.\n", command->info_out, strerror(errno));
        return (false);
    }
    command->fd_out = fd;
    dup2(fd, 1);
    return (true);
}

void close_redirections(command_t *command)
{
    if (command->fd_in != 0)
        close(command->fd_in);
    if (command->fd_out != 0)
        close(command->fd_out);
}
