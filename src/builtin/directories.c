/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Directory manipulations
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "varenv.h"

bool is_directory(char const *path)
{
    struct stat stats;
    int st = stat(path, &stats);

    if (st != -1 && S_ISDIR(stats.st_mode)) {
        fprintf(stderr, "%s: Permission denied.\n", path);
        return true;
    }
    return false;
}

void handle_cd(varenv_t **env, char *path)
{
    size_t size = strlen(path);

    if (size > 0 && path[0] == '-')
        handle_prev(env, path);
    else if (size > 0 && path[0] == '~')
        handle_home(env, path);
    else
        change_current_path(path);
}

void handle_prev(varenv_t **env, char const *path)
{
    varenv_t *oldpwd = varenv_get(*env, "OLDPWD");

    if (strlen(path) > 1)
        fprintf(stderr, "Usage: cd [-plvn][-|<dir>].\n");
    else if (oldpwd == NULL)
        fprintf(stderr, ": No such file or directory.\n");
    else
        change_current_path(oldpwd->value);
}

void change_current_path(char const *dir)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st != -1 && !S_ISDIR(stats.st_mode))
        fprintf(stderr, "%s: Not a directory.\n", dir);
    else if (chdir(dir) == -1)
        fprintf(stderr, "%s: No such file or directory.\n", dir);
}
