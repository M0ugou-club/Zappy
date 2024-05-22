/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connection
*/

#ifndef CONNECTION_H_
    #define CONNECTION_H_

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <stdbool.h>

typedef struct connection_s {
    int sockfd;
    struct sockaddr_in addr;
    char *buffer;
    char *team;
    struct connection_s *next;
} connection_t;

#endif /* !CONNECTION_H_ */
