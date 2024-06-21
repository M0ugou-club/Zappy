/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** new_connection
*/

#include "connection.h"

connection_t *new_connection(int fd, struct sockaddr_in *addr)
{
    connection_t *new = malloc(sizeof(connection_t));

    if (new == NULL)
        return NULL;
    new->fd = fd;
    new->addr = *addr;
    new->buffer = malloc(sizeof(char) * 1024);
    memset(new->buffer, 0, 1024);
    new->team = NULL;
    new->handshake_step = WELCOME;
    new->send_queue = NULL;
    memset(new->command_queue, 0, MAX_COMMAND_QUEUE);
    new->next = NULL;
    return new;
}
