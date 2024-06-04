/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** run_server
*/

#include "server.h"

static int get_max_fd(server_t *srv)
{
    int max = 0;
    connection_t *cl = srv->cons;

    while (cl != NULL) {
        if (cl->fd > max)
            max = cl->fd;
        cl = cl->next;
    }
    if (srv->sock->fd > max)
        max = srv->sock->fd;
    return max;
}

// TODO: rewrite this function with game data
static void accept_connection(server_t *srv)
{
    int newsockfd;
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof(cli_addr);
    char *buffer = malloc(sizeof(char) * 1024);
    connection_t *new = NULL;

    memset(buffer, 0, 1024);
    newsockfd = accept(srv->sock->fd, (struct sockaddr *)&cli_addr, &len);
    if (newsockfd < 0)
        return;
    SEND_FD(newsockfd, "WELCOME\n");
    read(newsockfd, buffer, 1024);
    new = new_connection(newsockfd,
        (struct sockaddr_in *)&cli_addr, buffer);
    srv->cons = add_connection(srv->cons, new);
    SEND_INT(new, 1);
    dprintf(new->fd, " %zu %zu\n", srv->args->x, srv->args->y);
    free(buffer);
}

// TODO: add game tick at end of while loop
void run_server(server_t *srv)
{
    int select_ret = 0;

    printf("Server started on port %zu\n", srv->args->port);
    while (true) {
        build_sets(srv, srv->cons);
        select_ret = select(get_max_fd(srv) + 1, srv->readfds,
            srv->writefds, NULL, NULL);
        if (select_ret < 0)
            return;
        if (FD_ISSET(srv->sock->fd, srv->readfds)) {
            accept_connection(srv);
            continue;
        }
        read_connections(srv);
        execute_connections(srv);
        send_messages(srv);
    }
}
