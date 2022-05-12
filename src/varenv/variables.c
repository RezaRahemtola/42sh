/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Variables management
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "varenv.h"

static int is_alphanumeric(const char *str)
{
    size_t size = strlen(str);
    int number;
    int lower;
    int upper;

    for (size_t i = 0; i < size; i++) {
        number = (str[i] >= '0' && str[i] <= '9');
        lower = (str[i] >= 'a' && str[i] <= 'z');
        upper = (str[i] >= 'A' && str[i] <= 'Z');
        if (!number && !lower && !upper && str[i] != '_')
            return (0);
    }
    return (1);
}

void add_variable(varenv_t **env, const char *key, const char *value)
{
    varenv_t *var = varenv_get(*env, key);

    if (var == NULL)
        varenv_put(env, strdup(key), strdup(value));
    else
        varenv_replace(*env, key, value);
}

int set_variable(varenv_t **env, const char *key, const char *value)
{
    char *alpha = "alphanumeric characters";

    if (is_alphanumeric(key)) {
        add_variable(env, key, value);
        return (0);
    } else {
        fprintf(stderr, "setenv: Variable name must contain %s.\n", alpha);
        return (1);
    }
}

varenv_t *convert_env(char **env)
{
    varenv_t *list = NULL;
    char *key = NULL;
    char *value = NULL;

    for (size_t i = 0; env[i] != NULL; i++) {
        key = extract_key(env[i]);
        value = extract_value(env[i]);
        if (key != NULL && value != NULL)
            varenv_put(&list, key, value);
        free(key);
        free(value);
    }
    return (list);
}

char **convert_varenv(varenv_t *list)
{
    int size = varenv_size(list);
    int index = 0;
    char **array = malloc(sizeof(char *) * (size + 1));
    varenv_t *current = list;

    if (array == NULL)
        return NULL;
    while (current != NULL) {
        array[index] = malloc(sizeof(char) * (strlen(current->key) +
                                              strlen(current->value) + 2));
        sprintf(array[index], "%s=%s", current->key, current->value);
        index++;
        current = current->next;
    }
    array[index] = NULL;
    return (array);
}
