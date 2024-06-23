/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_connection
*/

#include "server.h"

static void free_queue(connection_t *cl)
{
    char *tmp = player_dequeue(cl);

    while (tmp != NULL) {
        free(tmp);
        tmp = player_dequeue(cl);
    }
}

static void free_messages(connection_t *cl)
{
    for (int i = 0; cl->send_queue[i] != NULL; i++) {
        free(cl->send_queue[i]);
    }
    free(cl->send_queue);
}

void free_connection(connection_t *cons)
{
    connection_t *tmp = cons;
    connection_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        close(tmp->fd);
        free(tmp->buffer);
        free_queue(tmp);
        free_messages(tmp);
        free(tmp);
        tmp = next;
    }
}
