/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** set_game_properties
*/

#include "server.h"

int set_max_clients(args_t *args, char **argv, int *i, int argc)
{
    if (*i + 1 >= argc)
        return EXIT_ERROR;
    args->maxClients = atoi(argv[*i + 1]);
    return EXIT_SUCCESS;
}

int set_frequency(args_t *args, char **argv, int *i, int argc)
{
    if (*i + 1 >= argc)
        return EXIT_ERROR;
    args->frequency = atoi(argv[*i + 1]);
    return EXIT_SUCCESS;
}

int set_teams(args_t *args, char **argv, int *i, int argc)
{
    int count = 0;

    if (*i + 1 >= argc || argv[*i + 1][0] == '-')
        return EXIT_ERROR;
    for (int j = *i + 1; j < argc; j++) {
        if (argv[j][0] == '-')
            break;
        count++;
    }
    args->teams = malloc(sizeof(char *) * (count + 1));
    for (int j = 0; j < count; j++) {
        args->teams[j] = malloc(strlen(argv[*i + 1 + j]) + 1);
        strcpy(args->teams[j], argv[*i + 1 + j]);
    }
    args->teams[count] = NULL;
    *i += count;
    return EXIT_SUCCESS;
}
