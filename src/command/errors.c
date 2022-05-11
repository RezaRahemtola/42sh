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
#include "messages.h"

void handle_errors(int status)
{
    int sig;
    char const *core = (WCOREDUMP(status) ? CORE_DUMPED : "");

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        if (sig == SIGFPE)
            fprintf(stderr, "%s%s\n", FLOATING_EX, core);
        else
            fprintf(stderr, "%s%s\n", strsignal(sig), core);
    }
}
