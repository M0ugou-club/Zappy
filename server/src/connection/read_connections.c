/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** read_connections
*/

#include "server.h"

static bool action_setup(connection_t *conn)
{
    if (conn == NULL)
        return true;
    if (conn->buffer == NULL) {
        conn->buffer = malloc(BUFFER_SIZE);
        if (conn->buffer == NULL)
            return true;
        memset(conn->buffer, 0, BUFFER_SIZE);
    } else {
        conn->buffer = realloc(conn->buffer,
            sizeof(conn->buffer) + BUFFER_SIZE);
        if (conn->buffer == NULL)
            return true;
    }
    return false;
}

static void action(server_t *srv, int client_fd)
{
    connection_t *cli = get_client_by_fd(srv->cons, client_fd);
    char tmp[BUFFER_SIZE];
    ssize_t ret;

    if (action_setup(cli))
        return;
    ret = read(client_fd, tmp, BUFFER_SIZE - 1);
    if (ret <= 0) {
        remove_connection(&srv->cons, client_fd);
        close(client_fd);
        return;
    }
    tmp[ret] = '\0';
    memcpy(cli->buffer + strlen(cli->buffer), tmp, ret);
}

void read_connections(server_t *srv)
{
    connection_t *tmp = srv->cons;

    while (tmp != NULL) {
        if (FD_ISSET(tmp->fd, srv->readfds))
            action(srv, tmp->fd);
        tmp = tmp->next;
    }
}
