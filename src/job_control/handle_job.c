/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Handle job control
*/

#include <stdbool.h>
#include <stdio.h>
#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

bool job_command_case(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '&' && str[i + 1] == '\0') {
            return (true);
        } else if (str[i] == '&' && str[i + 1] == '&') {
            return (false);
        }
    }
    return (false);
}

job_t *add_new_job(job_t *command, char *input)
{
    job_t *tmp = NULL;
    job_t *new_elem = malloc(sizeof(job_t));

    new_elem->command = strdup(input);
    new_elem->nb_job = 1;
    new_elem->next = NULL;
    if (command == NULL) {
        command = new_elem;
    } else {
        tmp = command;
        new_elem->nb_job++;
        for (tmp = command; tmp->next != NULL; ++new_elem->nb_job)
            tmp = tmp->next;
        tmp->next = new_elem;
    }
    return (command);
}

list_t *add_job_pid(list_t *job, char *wanted, pid_t pid, int nb_job)
{
    job_t *tmp = NULL;

    if (job != NULL && job->data != NULL)
        tmp = job->data;
    while (job != NULL) {
        tmp = job->data;
        if (!strcmp(wanted, tmp->command) && nb_job == tmp->nb_job) {
            tmp->pid = pid;
            printf("[%d] %d\n", tmp->nb_job, tmp->pid);
            return (job);
        }
        job = job->next;
    }
    return (job);
}
