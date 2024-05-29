/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_server
*/

#include "server.h"

void free_server(server_t *server)
{
    free(server->args->teams);
    free(server->args);
    free(server->readfds);
    free(server->writefds);
    free(server->exceptfds);
    free(server->cons);
    free(server->sock);
    free(server->game);
    free(server);
}
