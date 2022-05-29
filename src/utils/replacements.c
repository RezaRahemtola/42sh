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

static env_t *get_alias(const char *command, env_t *aliases)
{
    while (aliases != NULL) {
        if (strcmp(aliases->key, command) == 0)
            return aliases;
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

static bool scan_argument(command_t *command, size_t index, shell_t *shell)
{
    size_t len = strlen(command->args[index]);
    bool out = true;

    for (size_t i = 0; i < len && out; i++) {
        if (len - i > 1 && strncmp("$?", &command->args[index][i], 2) == 0) {
            replace_test(command, shell, index, i);
            continue;
        }
        if (len - i > 1 && command->args[index][i] == '$') {
            out = replace_var(command, shell, index, i);
        }
    }
    return (out);
}

static bool replace_env_variables(command_t *command, shell_t *shell)
{
    bool out = true;
    size_t size = my_arraylen(command->args);

    for (size_t i = 0; i < size && out; i++) {
        out = scan_argument(command, i, shell);
    }
    if (!out)
        command->state = ABORTED;
    return (out);
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
