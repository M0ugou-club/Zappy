/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** send_message
*/

#include "server.h"

static void send_one_message(server_t *srv, connection_t *cl)
{
    dprintf(cl->fd, "%s", cl->send_queue[0]);
    free(cl->send_queue[0]);
    for (int i = 0; cl->send_queue[i + 1] != NULL; i++) {
        cl->send_queue[i] = cl->send_queue[i + 1];
    }
    cl->send_queue[get_array_size(cl->send_queue) - 1] = NULL;
}

void send_message(server_t *srv, connection_t *cl)
{
    if (cl == NULL)
        return;
    if (cl->send_queue[0] == NULL)
        return;
    if (!FD_ISSET(cl->fd, srv->writefds))
        return;
    send_one_message(srv, cl);
}
