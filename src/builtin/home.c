/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Home alias functions
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "builtin.h"
#include "environment.h"
#include "messages.h"
#include "my_string.h"
#include "shell.h"

void change_home(const env_t *env, const localenv_t *localenv)
{
    const env_t *home = get_env_value(env, "HOME");
    const localenv_t *localhome = get_localenv_value(localenv, "home");
    struct stat sb;
    int stat_status = stat((home == NULL ? "" : home->value), &sb);
    bool file = stat_status != -1 && !S_ISDIR(sb.st_mode);

    if (home == NULL || localhome == NULL)
        fprintf(stderr, "cd: %s\n", NO_HOME_DIR);
    else if (chdir(home->value) == -1 || file)
        fprintf(stderr, "cd: %s\n", HOME_DIR_ERROR);
}

int change_home_silently(shell_t *shell, const char *current)
{
    const env_t *home = get_env_value(shell->env, "HOME");
    const localenv_t *localhome = get_localenv_value(shell->localenv, "home");
    struct stat sb;
    int stat_status = stat((home == NULL ? "" : home->value), &sb);
    bool file = stat_status != -1 && !S_ISDIR(sb.st_mode);

    if (home == NULL || localhome == NULL || chdir(home->value) == -1 || file)
        return (1);
    add_variable(&shell->env, "PWD", home->value);
    add_localvar(&shell->localenv, "cwd", home->value, false);
    add_variable(&shell->env, "OLDPWD", current);
    add_localvar(&shell->localenv, "owd", current, false);
    exec_special_alias("cwdcmd", shell);
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
