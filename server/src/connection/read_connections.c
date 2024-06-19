/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** read_connections
*/

#include "connection.h"
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

static int strcount(const char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        count += str[i] == c;
    return count;

}

static void action(server_t *srv, connection_t *cli)
{
    char tmp[BUFFER_SIZE];
    ssize_t ret;

    if (action_setup(cli))
        return;
    ret = read(cli->fd, tmp, BUFFER_SIZE - 1);
    if (ret <= 0) {
        remove_connection(&srv->cons, cli->fd);
        close(cli->fd);
        return;
    }
    if (strcount(cli->buffer, '\n') > MAX_COMMAND_QUEUE)
        return;
    tmp[ret] = '\0';
    memcpy(cli->buffer + strlen(cli->buffer), tmp, ret);
}

void read_connections(server_t *srv)
{
    connection_t *tmp = srv->cons;

    while (tmp != NULL) {
        if (FD_ISSET(tmp->fd, srv->readfds))
            action(srv, tmp);
        tmp = tmp->next;
    }
}
