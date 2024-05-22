/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <unistd.h>
    #include "socket.h"
    #include "connection.h"

typedef struct {
    size_t port;
    size_t x;
    size_t y;
    char **teams;
    size_t maxClients;
    size_t frequency;
} args_t;

typedef struct server_s {
    args_t *args;
    sock_handle_t *sock;
    connection_t *cons;
    fd_set *readfds;
    fd_set *writefds;
    fd_set *exceptfds;
} server_t;

#endif /* !SERVER_H_ */
