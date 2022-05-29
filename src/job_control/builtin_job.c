/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Handle background and forwardground
*/

#include "types.h"
#include <stdio.h>

int silent_job(env_t **env, char *const *args, shell_t *shell)
{
    job_t *job = shell->job;
    size_t size = my_arraylen(args);

    if (size != 1) {
        fprintf(stderr, "jobs: Too many arguments.\n");
        return (1);
    }
    while (job != NULL) {
        printf("[%d]\tRunnig\t%s\n", job->nb_job, job->command);
        job = job->next;
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

int silent_fg(env_t **env, char *const *args, shell_t *shell)
{
    job_t *job = shell->job;
    size_t size = my_arraylen(args);
    bool found = false;
    int pid = 0;

    if (size != 2) {
        fprintf(stderr, "fg [PID].\n");
        return (1);
    }
    pid = atoi(args[1]);
    while (job != NULL) {
        if (pid == job->pid)
            found = true;
        job = job->next;
    }
    if (found)
        return (wait_fg(pid));
    fprintf(stderr, "fg: job not found: %d.\n", pid);
    return (1);
}
