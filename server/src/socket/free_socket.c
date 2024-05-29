/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_socket
*/

#include "socket.h"

void free_socket(sock_handle_t *sock)
{
    close(sock->fd);
    free(sock);
}
