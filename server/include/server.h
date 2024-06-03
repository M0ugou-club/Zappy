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
    #include <string.h>
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

typedef struct arg_match_s {
    char *arg;
    int (*func)(args_t *args, char **argv, int *i, int argc);
} arg_match_t;

typedef struct main_args_s {
    int argc;
    char **argv;
} main_args_t;

int set_port(args_t *args, char **argv, int *i, int argc);
int set_x(args_t *args, char **argv, int *i, int argc);
int set_y(args_t *args, char **argv, int *i, int argc);
int set_max_clients(args_t *args, char **argv, int *i, int argc);
int set_frequency(args_t *args, char **argv, int *i, int argc);
int set_teams(args_t *args, char **argv, int *i, int argc);

args_t *get_args(int argc, char **argv);
void free_args(args_t *args);


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
void run_server(server_t *server);

#endif /* !SERVER_H_ */
