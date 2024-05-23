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

typedef struct connection_s {
    int fd;
    struct sockaddr_in addr;
    char *buffer;
    char *team;
    struct connection_s *next;
} connection_t;

connection_t *add_connection(connection_t *cons, connection_t *new);
void free_connection(connection_t *cons);
connection_t *new_connection(int fd, struct sockaddr_in addr, char *team);

#endif /* !CONNECTION_H_ */
