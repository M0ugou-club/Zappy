/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** send_messages
*/

#include "server.h"

void send_messages(server_t *srv)
{
    connection_t *tmp = srv->cons;

    while (tmp != NULL) {
        if (tmp->send_queue != NULL) {
            send_message(srv, tmp);
        }
        tmp = tmp->next;
    }
}
