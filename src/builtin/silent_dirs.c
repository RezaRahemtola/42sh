/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Silent directory checks
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"
#include "environment.h"

static int handle_prev_silently(env_t **env, const char *path, const char *curr)
{
    const env_t *oldpwd = get_env_value(*env, "OLDPWD");

    if (strlen(path) > 1 || oldpwd == NULL)
        return (1);
    return (change_dir_silently(env, oldpwd->value, curr));
}

int handle_cd_silently(env_t **env, const char *path, const char *current)
{
    size_t size = strlen(path);

    if (size > 0 && path[0] == '-')
        return (handle_prev_silently(env, path, current));
    return (change_dir_silently(env, path, current));
}

int change_dir_silently(env_t **env, const char *dir, const char *current)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st == -1 || !S_ISDIR(stats.st_mode) || chdir(dir) == -1)
        return (1);
    add_variable(env, "PWD", dir);
    add_variable(env, "OLDPWD", current);
    return (0);
}
