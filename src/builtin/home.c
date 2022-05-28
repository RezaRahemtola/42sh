/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Home alias functions
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "shell.h"
#include "environment.h"
#include "my_string.h"

void change_home(const env_t *env)
{
    const env_t *home = get_env_value(env, "HOME");
    struct stat stats;
    int stat_status = stat((home == NULL ? "" : home->value), &stats);
    bool file = stat_status != -1 && !S_ISDIR(stats.st_mode);

    if (home == NULL)
        fprintf(stderr, "cd: No home directory.\n");
    else if (chdir(home->value) == -1 || file)
        fprintf(stderr, "cd: Can't change to home directory.\n");
}

int change_home_silently(env_t **env, const char *current)
{
    const env_t *home = get_env_value(*env, "HOME");
    struct stat stats;
    int stat_status = stat((home == NULL ? "" : home->value), &stats);
    bool file = stat_status != -1 && !S_ISDIR(stats.st_mode);

    if (home == NULL || chdir(home->value) == -1 || file)
        return (1);
    add_variable(env, "PWD", home->value);
    add_variable(env, "OLDPWD", current);
    return (0);
}

bool is_builtin(const char *command)
{
    if (command == NULL)
        return (false);
    for (size_t i = 0; BUILTIN[i].command != NULL; i++)
        if (strcmp(command, BUILTIN[i].command) == 0)
            return (true);
    return (false);
}
