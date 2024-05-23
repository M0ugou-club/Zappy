/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_socket
*/

#include "socket.h"

static bool socket_creation(sock_handle_t *sock, size_t port)
{
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1)
        return false;
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_port = htons(port);
    sock->addr.sin_addr.s_addr = INADDR_ANY;
    if (setsockopt(sock->fd, SOL_SOCKET,
        SO_REUSEADDR, &(int){1}, sizeof(int)) == -1)
        return false;
    if (bind(sock->fd,
        (struct sockaddr *)&sock->addr, sizeof(sock->addr)) == -1)
        return false;
    if (listen(sock->fd, 0) == -1)
        return false;
    return true;
}

sock_handle_t *init_socket(size_t port)
{
    sock_handle_t *sock = malloc(sizeof(sock_handle_t));
    struct sockaddr_in addr;

    sock->addr = addr;
    if (!socket_creation(sock, port)) {
        free(sock);
        return NULL;
    }
    return sock;
}
