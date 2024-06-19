/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** closer_server
*/

#include "server.h"

void close_server(const int signal, void *sr)
{
    server_t *srv = (server_t *)sr;

    if (signal == SIGINT) {
        printf("Server closing\n");
        srv->close = true;
    }
}
