/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_connection
*/

#include "connection.h"

void free_connection(connection_t *cons)
{
    connection_t *tmp = cons;
    connection_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->buffer);
        free(tmp->team);
        free(tmp);
        tmp = next;
    }
}
