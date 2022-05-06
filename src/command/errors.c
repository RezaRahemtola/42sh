/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Errors handling
*/

#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "my.h"

void handle_errors(int status)
{
    int sig = 0;
    char *core = (WCOREDUMP(status) ? " (core dumped)" : "");

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        if (sig == SIGFPE) {
            my_dprintf(2, "Floating exception%s\n", core);
        } else {
            my_dprintf(2, "%s%s\n", strsignal(sig), core);
        }
    }
}
