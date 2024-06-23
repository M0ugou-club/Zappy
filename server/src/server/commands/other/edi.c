/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** edi
*/

#include "server.h"

void edi(server_t *srv, connection_t *cl, egg_t *egg)
{
    queue_formatted_message(cl, "edi %d\n", egg->id);
}
