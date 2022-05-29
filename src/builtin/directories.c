/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Directory manipulations
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "environment.h"
#include "messages.h"
#include "shell.h"

bool is_directory(const char *path)
{
    struct stat stats;
    int st = stat(path, &stats);

    if (st != -1 && S_ISDIR(stats.st_mode)) {
        fprintf(stderr, "%s: %s\n", path, FOLDER_ERROR);
        return true;
    }
    return false;
}

static void handle_prev(const env_t *env, const char *path)
{
    const env_t *oldpwd = get_env_value(env, "OLDPWD");

    if (strlen(path) > 1)
        fprintf(stderr, "%s\n", CD_USAGE);
    else if (oldpwd == NULL)
        fprintf(stderr, ": %s\n", NO_FILE);
    else
        change_current_path(oldpwd->value);
}

void handle_cd(const env_t *env, const char *path)
{
    size_t size = strlen(path);

    if (size > 0 && path[0] == '-')
        handle_prev(env, path);
    else
        change_current_path(path);
}

void change_current_path(const char *dir)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st != -1 && !S_ISDIR(stats.st_mode))
        fprintf(stderr, "%s: %s\n", dir, NOT_DIRECTORY);
    else if (chdir(dir) == -1)
        fprintf(stderr, "%s: %s\n", dir, NO_FILE);
}
