/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Directory manipulations
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "environment.h"

bool is_directory(const char *path)
{
    struct stat stats;
    int st = stat(path, &stats);

    if (st != -1 && S_ISDIR(stats.st_mode)) {
        fprintf(stderr, "%s: Permission denied.\n", path);
        return true;
    }
    return false;
}

void handle_cd(env_t **env, const char *path)
{
    size_t size = strlen(path);

    if (size > 0 && path[0] == '-')
        handle_prev(env, path);
    else if (size > 0 && path[0] == '~')
        handle_home(env, path);
    else
        change_current_path(path);
}

void handle_prev(env_t **env, const char *path)
{
    env_t *oldpwd = get_env_value(*env, "OLDPWD");

    if (strlen(path) > 1)
        fprintf(stderr, "Usage: cd [-plvn][-|<dir>].\n");
    else if (oldpwd == NULL)
        fprintf(stderr, ": No such file or directory.\n");
    else
        change_current_path(oldpwd->value);
}

void change_current_path(const char *dir)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st != -1 && !S_ISDIR(stats.st_mode))
        fprintf(stderr, "%s: Not a directory.\n", dir);
    else if (chdir(dir) == -1)
        fprintf(stderr, "%s: No such file or directory.\n", dir);
}
