/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_client_by_fd
*/

#include "server.h"

connection_t *get_client_by_fd(connection_t *cl, int sockfd)
{
    connection_t *tmp = cl;

    while (tmp != NULL) {
        if (tmp->fd == sockfd)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
