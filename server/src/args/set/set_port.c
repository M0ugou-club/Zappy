/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** set_port
*/

#include "server.h"

int set_port(args_t *args, char **argv, int *i, int argc)
{
    if (*i + 1 >= argc)
        return EXIT_ERROR;
    args->port = atoi(argv[*i + 1]);
    return EXIT_SUCCESS;
}
