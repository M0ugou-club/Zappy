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

typedef struct sock_handle {
    int fd;
    struct sockaddr_in addr;
    int listen;
    int bind;
    int opt;
} sock_handle_t;

#endif /* !SOCKET_H_ */
