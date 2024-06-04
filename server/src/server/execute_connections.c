/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** execute_connections
*/

#include "server.h"

static char *get_arg(const char *src, size_t start, size_t end)
{
    char *dest = malloc(end - start + 1);

    if (dest == NULL)
        return NULL;
    memset(dest, 0, end - start + 1);
    for (size_t i = start; i < end; i++)
        dest[i - start] = src[i];
    return dest;
}

// TODO: Implement the regex parsing
static void execute(char *cmd, int client_fd, server_t *srv)
{
    return;
}

static char *new_buffer(connection_t *client, char *tmp)
{
    char *tmp2 = NULL;

    if (tmp - client->buffer - 2 <= 0) {
        free(client->buffer);
        return NULL;
    }
    tmp2 = malloc(tmp - client->buffer - 2);
    if (tmp2 == NULL)
        return NULL;
    memset(tmp2, 0, tmp - client->buffer - 2);
    memcpy(tmp2, tmp + 2, tmp - client->buffer - 2);
    free(client->buffer);
    return tmp2;
}

static void execute_client(connection_t *client, server_t *srv)
{
    char *tmp = NULL;
    char *tmp2 = NULL;

    if (client->buffer == NULL)
        return;
    tmp = strstr(client->buffer, "\n");
    if (tmp == NULL)
        return;
    tmp2 = get_arg(client->buffer, 0, tmp - client->buffer);
    if (tmp2 == NULL)
        return;
    if (*tmp2 != '\0')
        execute(tmp2, client->fd, srv);
    if (client->buffer != NULL)
        client->buffer = new_buffer(client, tmp);
    free(tmp2);
}

void execute_connections(server_t *srv)
{
    connection_t *tmp = srv->cons;

    while (tmp != NULL) {
        if (FD_ISSET(tmp->fd, srv->writefds))
            execute_client(tmp, srv);
        tmp = tmp->next;
    }
}
