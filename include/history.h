/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** History'
*/

#pragma once

#include "types.h"

// Core
void replace_history(char **input, shell_t *shell);

// Interact
void add_history(const char *input, shell_t *shell);
void free_history(void *elem);
char *get_history_command(list_t *history, int index);
char *get_history_by_str(list_t *history, const char *str);

// Substitution
void handle_last_substitution(char **input, list_t *history);
void handle_nb_substitution(char **input, char *current, list_t *history);
void handle_str_substitution(char **input, char *current, list_t *history);
