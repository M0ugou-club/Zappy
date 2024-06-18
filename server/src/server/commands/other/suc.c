/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** suc
*/

#include "server.h"

void suc(server_t *srv, connection_t *cl)
{
    queue_formatted_message(cl, "suc\n");
}
