/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** error_args
*/

#include "server.h"

bool error_args(args_t *args)
{
    if (args->port <= 0 || args->x <= 0 || args->y <= 0 || args->teams == NULL)
        return true;
    return false;
}
