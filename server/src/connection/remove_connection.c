/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** remove_connection
*/

#include "server.h"

static bool remove_first(connection_t **cl, int sockfd, connection_t *tmp)
{
    if (tmp != NULL && tmp->fd == sockfd) {
        *cl = tmp->next;
        close(tmp->fd);
        free(tmp->buffer);
        free(tmp->send_queue);
        free(tmp);
        return true;
    }
    return false;
}

void remove_connection(connection_t **cl, int sockfd)
{
    connection_t *tmp = *cl;
    connection_t *prev = NULL;

    printf("Removing connection fd: %d\n", sockfd);
    if (remove_first(cl, sockfd, tmp))
        return;
    while (tmp != NULL && tmp->fd != sockfd) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    close(tmp->fd);
    free(tmp->buffer);
    free(tmp->send_queue);
    free(tmp);
}
