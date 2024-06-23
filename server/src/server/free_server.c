/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_server
*/

#include "server.h"

static void disconnect_all(server_t *srv)
{
    connection_t *tmp = srv->cons;
    connection_t *next = NULL;

    while (tmp) {
        next = tmp->next;
        close(tmp->fd);
        free_connection(tmp);
        tmp = next;
    }
}

void free_server(server_t *server)
{
    free_args(server->args);
    free(server->readfds);
    free(server->writefds);
    free_socket(server->sock);
    free_connection(server->cons);
    free_game(server->game);
    free(server);
}
