/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0

    #include <unistd.h>
    #include <stdlib.h>
    #include "socket.h"
    #include "connection.h"
    #include "game.h"

typedef struct args_s {
    size_t port;
    size_t x;
    size_t y;
    char **teams;
    size_t maxClients;
    size_t frequency;
} args_t;

typedef struct server_s {
    struct args_s *args;
    sock_handle_t *sock;
    connection_t *cons;
    game_t *game;
    fd_set *readfds;
    fd_set *writefds;
    fd_set *exceptfds;
} server_t;

server_t *init_server(args_t *args);
void free_server(server_t *server);

#endif /* !SERVER_H_ */
