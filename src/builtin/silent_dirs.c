/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Silent directory checks
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "environment.h"
#include "shell.h"

static int handle_prev_silently(shell_t *shell, const char *path,
const char *current)
{
    const env_t *oldpwd = get_env_value(shell->env, "OLDPWD");

    if (strlen(path) > 1 || oldpwd == NULL)
        return (1);
    return (change_dir_silently(shell, oldpwd->value, current));
}

int handle_cd_silently(shell_t *shell, const char *path, const char *current)
{
    size_t size = strlen(path);

    if (size > 0 && path[0] == '-')
        return (handle_prev_silently(shell, path, current));
    return (change_dir_silently(shell, path, current));
}

int change_dir_silently(shell_t *shell, const char *dir, const char *current)
{
    struct stat sb;
    char *path = NULL;

    if (stat(dir, &sb) == -1 || !S_ISDIR(sb.st_mode) || chdir(dir) == -1)
        return (1);
    path = getcwd(NULL, 0);
    add_variable(&shell->env, "PWD", path);
    add_localvar(&shell->localenv, "cwd", path, false);
    add_variable(&shell->env, "OLDPWD", current);
    add_localvar(&shell->localenv, "owd", current, false);
    exec_special_alias("cwdcmd", shell);
    free(path);
    return (0);
}
