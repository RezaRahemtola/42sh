/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Remove case if there is zombie job
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include "types.h"
#include "jobs.h"

bool compare_pid(void *list_elem, void *compare)
{
    job_t *old = list_elem;
    int status = 0;

    (void)compare;
    if (waitpid(old->pid, &status, WNOHANG)) {
        printf("[%d] Done -> %s\n", old->nb_job, old->command);
        return (true);
    } else {
        return (false);
    }
}

void free_pid(void *elem)
{
    job_t *job = elem;

    free(job->command);
    free(job);
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
