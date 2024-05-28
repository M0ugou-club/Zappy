/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_connection
*/

#include "connection.h"

connection_t *add_connection(connection_t *cons, connection_t *new)
{
    connection_t *tmp = cons;

    if (cons == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return cons;
}
