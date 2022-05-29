/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Handle background and forwardground
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_arrays.h"
#include "shell.h"

int silent_jobs(shell_t *shell, char *const *args)
{
    list_t *cp = shell->job;
    job_t *job = NULL;
    size_t size = my_arraylen(args);

    if (size != 1) {
        fprintf(stderr, "jobs: Too many arguments.\n");
        return (1);
    }
    while (cp != NULL) {
        job = cp->data;
        printf("[%d]\tRunning\t%s\n", job->nb_job, job->command);
        cp = cp->next;
    }
    return (0);
}

int wait_fg(pid_t pid)
{
    int status = 0;

    tcsetpgrp(0, pid);
    if (isatty(0))
        waitpid(pid, &status, WUNTRACED | WCONTINUED);
    handle_errors(status);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, getpid());
    signal(SIGTTOU, SIG_DFL);
    return (status > 255 ? status / 256 : status);
}

static bool error_case_fg(shell_t *shell, char *const *args)
{
    if (shell->job == NULL || shell->job->data == NULL) {
        fprintf(stderr, "fg: No current job.\n");
        return (false);
    }
    if (my_arraylen(args) != 2) {
        fprintf(stderr, "fg: No current job.\n");
        return (false);
    }
    return (true);
}

int silent_fg(shell_t *shell, char *const *args)
{
    job_t *job = NULL;
    int nb_job = 0;

    if (!error_case_fg(shell, args))
        return (1);
    job = shell->job->data;
    nb_job = atoi(args[1]);
    while (shell->job != NULL) {
        job = shell->job->data;
        if (nb_job == job->nb_job) {
            return (wait_fg(job->pid));
        }
        shell->job = shell->job->next;
    }
    fprintf(stderr, "fg: No such job.\n");
    return (1);
}
