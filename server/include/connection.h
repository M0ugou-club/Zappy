/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connection
*/

#ifndef CONNECTION_H_
    #define CONNECTION_H_

    #include <stdlib.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <stdbool.h>
    #include <string.h>

    #define MAX_COMMAND_QUEUE 10

typedef enum handshake_step_e {
    WELCOME,
    TEAM,
    ESTABLISHED
} handshake_step_t;

typedef struct connection_s {
    int fd;
    struct sockaddr_in addr;
    char *buffer;
    char **send_queue;
    char *command_queue[MAX_COMMAND_QUEUE];
    char *team;
    handshake_step_t handshake_step;
    struct connection_s *next;
} connection_t;

connection_t *add_connection(connection_t *cons, connection_t *new);
void free_connection(connection_t *cons);
connection_t *new_connection(int fd, struct sockaddr_in *addr);

#endif /* !CONNECTION_H_ */
