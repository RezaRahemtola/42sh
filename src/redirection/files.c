/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** File redirections
*/

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "my_string.h"

static void read_input(command_t *command)
{
    bool out = false;
    char *str = strdup("");
    char *cat = NULL;
    char *content = NULL;
    size_t size = 0;

    while (!out) {
        printf("? ");
        size = getline(&content, &size, stdin);
        if ((int) size == -1 || strcmp(content, command->info_in) == '\n') {
            out = true;
        } else {
            cat = my_strcat(str, content);
            free(str);
            str = cat;
        }
    }
}

bool open_input_redirection(command_t *command)
{
    int fd = 0;
    separator_in_t separator = command->separator_in;

    if (separator != FILE_READ && separator != INPUT_READ) {
        return (true);
    }
    if (separator == INPUT_READ) {
        read_input(command);
        return (true);
    }
    fd = open(command->info_in, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: %s.\n", command->info_in, strerror(errno));
        return (false);
    }
    command->fd_in = fd;
    dup2(fd, 0);
    return (true);
}

bool open_output_redirection(command_t *command)
{
    int fd = 0;
    int flags = 0;
    separator_out_t separator = command->separator_out;

    if (separator != FILE_WRITE && separator != FILE_APPEND) {
        return (true);
    }
    if (separator == FILE_WRITE) {
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    } else {
        flags = O_CREAT | O_WRONLY | O_APPEND;
    }
    fd = open(command->info_out, flags, 0664);
    if (fd == -1) {
        fprintf(stderr, "%s: %s.\n", command->info_out, strerror(errno));
        return (false);
    }
    command->fd_out = fd;
    dup2(fd, 1);
    return (true);
}

void close_input_redirection(command_t *command)
{
    if (command->fd_in != 0) {
        close(command->fd_in);
    }
}

void close_output_redirection(command_t *command)
{
    if (command->fd_out != 0) {
        close(command->fd_out);
    }
}
