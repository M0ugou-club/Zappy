/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** seg
*/

#include "server.h"

void seg(server_t *srv, connection_t *cl, char *team_name)
{
    queue_formatted_message(cl, "seg %s\n", team_name);
}
