/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** broadcast_gui
*/

#include "connection.h"
#include "server.h"

void broadcast_gui(server_t *srv, char *fmt, ...)
{
    va_list args;
    char *msg;
    size_t size = 0;

    va_start(args, fmt);
    size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    msg = malloc(size + 1);
    if (msg == NULL)
        return;
    va_start(args, fmt);
    vsnprintf(msg, size + 1, fmt, args);
    va_end(args);
    for (connection_t *tmp = srv->cons; tmp; tmp = tmp->next)
        if (tmp->handshake_step == ESTABLISHED
            && strcmp(tmp->team, "GRAPHIC") == 0)
            queue_message(tmp, msg);
    free(msg);
}
