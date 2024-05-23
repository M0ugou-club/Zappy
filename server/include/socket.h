/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** socket
*/

#ifndef SOCKET_H_
    #define SOCKET_H_

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <unistd.h>

typedef struct sock_handle {
    int fd;
    struct sockaddr_in addr;
    int listen;
    int bind;
    int opt;
} sock_handle_t;

sock_handle_t *init_socket(size_t port);
void free_socket(sock_handle_t *sock);

#endif /* !SOCKET_H_ */
