/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Errors handling
*/

#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include "my.h"

void handle_errors(int status)
{
    int sig = 0;
    char *core = (WCOREDUMP(status) ? " (core dumped)" : "");

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        if (sig == SIGFPE) {
            fprintf(stderr, "Floating exception%s\n", core);
        } else {
            fprintf(stderr, "%s%s\n", strsignal(sig), core);
        }
    }
}
