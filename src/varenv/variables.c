/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Variables management
*/

#include <stdlib.h>
#include "my_string.h"
#include "my.h"
#include "varenv.h"

static int is_alphanumeric(char *str)
{
    int size = my_strlen(str);
    int number = 0;
    int lower = 0;
    int upper = 0;

    for (int i = 0; i < size; i++) {
        number = (str[i] >= '0' && str[i] <= '9');
        lower = (str[i] >= 'a' && str[i] <= 'z');
        upper = (str[i] >= 'A' && str[i] <= 'Z');
        if (!number && !lower && !upper && str[i] != '_') {
            return (0);
        }
    }
    return (1);
}

void add_variable(varenv_t **env, char *key, char *value)
{
    varenv_t *var = varenv_get(*env, key);

    if (var == NULL) {
        varenv_put(env, my_strdup(key), my_strdup(value));
    } else {
        varenv_replace(*env, key, my_strdup(value));
    }
}

void set_variable(varenv_t **env, char *key, char *value, minishell_t *shell)
{
    char *alpha = "alphanumeric characters";

    if (is_alphanumeric(key)) {
        add_variable(env, key, value);
        shell->ret = 0;
    } else {
        my_dprintf(2, "setenv: Variable name must contain %s.\n", alpha);
        shell->ret = 1;
    }
}

varenv_t *convert_env(char **env)
{
    varenv_t *list = NULL;
    char *key = NULL;
    char *value = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        key = extract_key(env[i]);
        value = extract_value(env[i]);
        if (key != NULL && value != NULL) {
            varenv_put(&list, key, value);
        }
    }
    return (list);
}

char **convert_varenv(varenv_t *list)
{
    int size = varenv_size(list);
    int index = 0;
    char **array = malloc(sizeof(char *) * (size + 1));
    varenv_t *current = list;

    if (array == NULL) {
        return NULL;
    }
    while (current != NULL) {
        array[index] = my_stringf("%s=%s", current->key, current->value);
        index++;
        current = current->next;
    }
    array[index] = NULL;
    return (array);
}
