/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** sbp
*/

#include "server.h"

void sbp(server_t *srv, connection_t *cl)
{
    queue_formatted_message(cl, "sbp\n");
}
