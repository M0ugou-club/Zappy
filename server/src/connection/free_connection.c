/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_connection
*/

#include "server.h"

void free_connection(connection_t *cons)
{
    connection_t *tmp = cons;
    connection_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        close(tmp->fd);
        free(tmp->buffer);
        free(tmp->team);
        free(tmp);
        tmp = next;
    }
}
