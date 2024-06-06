/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_args
*/

#include "server.h"

void free_args(args_t *args)
{
    for (size_t i = 0; args->teams[i] != NULL; i++)
        free(args->teams[i]);
    free(args->teams);
    free(args);
}
