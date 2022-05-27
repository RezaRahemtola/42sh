/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Values replacements
*/

#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "my_arrays.h"
#include "my_string.h"
#include "my.h"
#include "shell.h"

void replace_argument(command_t *command, size_t index, char *new_arg)
{
    char *replaced = my_strrep(command->input, command->args[index], new_arg);
    if (replaced == NULL) {
        return;
    }
    my_free(2, command->input, command->args[index]);
    command->input = replaced;
    command->args[index] = new_arg;
}

static env_t *get_alias(char *command, env_t *aliases)
{
    while (aliases != NULL) {
        if (strcmp(aliases->key, command) == 0) {
            return aliases;
        }
        aliases = aliases->next;
    }
    return (NULL);
}

void replace_aliases(command_t *commands, env_t *aliases, env_t *env)
{
    char *first = NULL;
    char *input = NULL;
    env_t *alias = NULL;

    while (commands != NULL) {
        first = commands->args[0];
        alias = (first == NULL ? NULL : get_alias(first, aliases));
        if (alias != NULL) {
            free(commands->path);
            my_free_arrays(1, commands->args);
            input = commands->input;
            commands->input = my_strrep(input, alias->key, alias->value);
            commands->args = my_strsplit_many(commands->input, " \t");
            commands->path = find_command(env, commands->args[0]);
            free(input);
        }
        commands = commands->next;
    }
}

static bool replace_env_variables(command_t *command, shell_t *shell)
{
    bool out = true;
    size_t size = my_arraylen(command->args);
    size_t len = 0;

    for (size_t i = 0; i < size && out; i++) {
        len = strlen(command->args[i]);
        if (len > 1 && strncmp("$?", command->args[i], 2) == 0) {
            replace_test(command, shell, i);
            continue;
        }
        if (len > 1 && command->args[i][0] == '$') {
            out = replace_variable(command, shell, i);
        }
    }
    if (!out)
        command->state = ABORTED;
    return (true);
}

void replace_variables(command_t *command, shell_t *shell)
{
    size_t size = my_arraylen(command->args);

    if (!replace_env_variables(command, shell))
        return;
    if (!replace_home(command, shell, size)) {
        command->state = SKIPPED;
        command->ret = 1;
    }
}
