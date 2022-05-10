/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Errors handling
*/

#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "messages.h"
#include "my.h"

void handle_errors(int status)
{
    int sig = 0;
    const char *core = (WCOREDUMP(status) ? CORE_DUMPED : "");

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        if (sig == SIGFPE) {
            my_dprintf(2, "%s%s\n", FLOATING_EX, core);
        } else {
            my_dprintf(2, "%s%s\n", strsignal(sig), core);
        }
    }
}
