/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** build_sets
*/

#include "server.h"

void build_sets(server_t *srv, connection_t *conn)
{
    connection_t *tmp = conn;

    FD_ZERO(srv->readfds);
    FD_ZERO(srv->writefds);
    FD_SET(srv->sock->fd, srv->readfds);
    while (tmp != NULL) {
        FD_SET(tmp->fd, srv->readfds);
        FD_SET(tmp->fd, srv->writefds);
        tmp = tmp->next;
    }
}
