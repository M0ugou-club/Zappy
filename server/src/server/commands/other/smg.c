/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** smg
*/

#include "server.h"

void smg(server_t *srv, connection_t *cl, char *message)
{
    queue_formatted_message(cl, "smg %s\n", message);
}
