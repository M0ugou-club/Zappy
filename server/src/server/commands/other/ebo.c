/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** ebo
*/

#include "server.h"

void ebo(server_t *srv, connection_t *cl, egg_t *egg)
{
    queue_formatted_message(cl, "ebo #%d\n", egg->id);
}
