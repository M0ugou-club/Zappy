/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** closer_server
*/

#include "server.h"

void close_server(const int signal, void *srv)
{
    static server_t *saved = NULL;

    if (saved == NULL)
        saved = (server_t *)srv;
    if (signal == SIGINT) {
        printf("Server closing\n");
        saved->close = true;
    }
}
