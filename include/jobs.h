/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Jobs Header
*/

#pragma once

#include "types.h"

list_t *check_children(list_t *job);

bool compare_pid(void *list_elem, void *compare);
void free_pid(void *elem);

job_t *add_new_job(job_t *command, char *input);
list_t *add_job_pid(list_t *job, char *wanted, pid_t pid, int nb_job);
bool job_command_case(char *str);

char **remove_incorrect_char(char **input);
