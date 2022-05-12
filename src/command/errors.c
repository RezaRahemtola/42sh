/*
** EPITECH PROJECT, 2022
** 42sh
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
    int sig = 0;
    const char *core = (WCOREDUMP(status) ? CORE_DUMPED : "");

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        if (sig == SIGFPE)
            fprintf(stderr, "%s%s\n", FLOATING_EX, core);
        else
            fprintf(stderr, "%s%s\n", strsignal(sig), core);
    }
}
