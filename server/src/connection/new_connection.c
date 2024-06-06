/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** new_connection
*/

#include "connection.h"

connection_t *new_connection(int fd, struct sockaddr_in *addr, char *team)
{
    connection_t *new = malloc(sizeof(connection_t));

    if (new == NULL)
        return NULL;
    new->fd = fd;
    new->addr = *addr;
    new->buffer = malloc(sizeof(char) * 1024);
    new->team = strdup(team);
    new->next = NULL;
    return new;
}
