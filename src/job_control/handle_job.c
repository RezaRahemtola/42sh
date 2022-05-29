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

bool job_command_case(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '&' && command[i + 1] != '&') {
            return (true);
        }
    }
    return (false);
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

job_t *add_new_job(job_t *command, char *input)
{
    job_t *tmp = NULL;
    job_t *new_elem = NULL;

    new_elem = malloc(sizeof(job_t));
    new_elem->command = strdup(input);;
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

job_t *add_job_pid(job_t *job, char *wanted, pid_t pid, int nb_job)
{
    job_t *tmp = job;

    while (tmp != NULL) {
        if (!strcmp(wanted, tmp->command) && nb_job == tmp->nb_job) {
            tmp->pid = pid;
            printf("[%d] %d\n", tmp->nb_job, tmp->pid);
            return (job);
        }
        tmp = tmp->next;
    }
    return (job);
}
