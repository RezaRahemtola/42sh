/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Remove case if there is zombie job
*/

#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

job_t *remove_job(job_t *job, pid_t wanted)
{
    job_t *redirect = NULL;
    job_t *tmp = job;

    if (tmp != NULL && tmp->next == NULL && tmp->pid == wanted) {
        return (tmp);
    }
    while (tmp != NULL) {
        tmp = tmp->next;
    }
}

char **remove_incorrect_char(char **input)
{
    for (int i = 0; input[i] != NULL; i++) {
        if (job_command_case(input[i])) {
            input[i] = NULL;
            return (input);
        }
    }
    return (input);
}

job_t *check_children(job_t *job)
{
    job_t *tmp = job;

    while (tmp != NULL) {
        if (kill(tmp->pid, SIGCHLD) < 0) {
            printf("[%d] Done -> %s\n", tmp->nb_job, tmp->command);
        }
        tmp = tmp->next;
    }
    return (job);
}
