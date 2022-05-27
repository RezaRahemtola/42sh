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
#include "shell.h"

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

void replace_variables(command_t *command, shell_t *shell)
{
    size_t size = my_arraylen(command->args);

    if (!replace_home(command, shell, size)) {
        command->state = SKIPPED;
        command->ret = 1;
        return;
    }
}
