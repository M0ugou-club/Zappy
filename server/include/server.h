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

    #define BUFFER_SIZE 1024

    #define SEND(conn, msg) write(conn->fd, msg, strlen(msg))
    #define SEND_INT(conn, msg) dprintf(conn->fd, "%d", msg)
    #define SEND_FD(fd, msg) write(fd, msg, strlen(msg))
    #define SEND_INT_FD(fd, msg) dprintf(fd, "%d", msg)

    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "socket.h"
    #include "connection.h"
    #include "game.h"

int get_array_size(char **arr);

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
bool error_args(args_t *args);

typedef struct server_s {
    struct args_s *args;
    sock_handle_t *sock;
    connection_t *cons;
    game_t *game;
    fd_set *readfds;
    fd_set *writefds;
} server_t;

void build_sets(server_t *srv, connection_t *conn);
connection_t *get_client_by_fd(connection_t *cl, int sockfd);
void remove_connection(connection_t **cl, int sockfd);

void read_connections(server_t *srv);
void execute_connections(server_t *srv);

void queue_message(connection_t *conn, char *msg);
void send_message(server_t *srv, connection_t *cl);
void send_messages(server_t *srv);

server_t *init_server(args_t *args);
void free_server(server_t *server);
void run_server(server_t *server);

#endif /* !SERVER_H_ */
