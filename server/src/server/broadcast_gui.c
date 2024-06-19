/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** broadcast_gui
*/

#include <stdarg.h>
#include <stdio.h>
#include "server.h"

void broadcast_gui(server_t *srv, char *format, ...)
{
    va_list args;
    char *msg = NULL;

    va_start(args, format);
    vsprintf(msg, format, args);
    va_end(args);
    for (connection_t *tmp = srv->cons; tmp; tmp = tmp->next) {
        if (strcmp(tmp->team, "GRAPHIC") == 0)
            queue_message(tmp, msg);
    }
    free(msg);
}
