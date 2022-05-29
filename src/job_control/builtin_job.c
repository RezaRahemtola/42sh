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

    while (job != NULL) {
        printf("[%d]\tRunnig\t%s\n", job->nb_job, job->command);
        job = job->next;
    }
}
