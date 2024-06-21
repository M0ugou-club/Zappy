/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** run_server
*/

#include "connection.h"
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

void clean_str(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n')
            str[i] = '\0';
        if (str[i] == '\r')
            str[i] = '\0';
    }
}

// also close if team is full / no eggs available
static void accept_connection(server_t *srv)
{
    int newsockfd;
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof(cli_addr);
    connection_t *new = NULL;

    newsockfd = accept(srv->sock->fd, (struct sockaddr *)&cli_addr, &len);
    if (newsockfd < 0)
        return;
    new = new_connection(newsockfd, (struct sockaddr_in *)&cli_addr);
    if (new == NULL)
        return;
    printf("New connection from %s:%d\n", inet_ntoa(cli_addr.sin_addr),
        ntohs(cli_addr.sin_port));
    queue_message(new, "WELCOME\n");
    new->handshake_step = TEAM;
    srv->cons = add_connection(srv->cons, new);
}

static int get_connections_count(connection_t *cl)
{
    int count = 0;

    while (cl != NULL) {
        count++;
        cl = cl->next;
    }
    return count;
}

static void actions(server_t *srv)
{
    read_connections(srv);
    execute_connections(srv);
    execute_ai_commands(srv);
    game_tick(srv);
    send_messages(srv);
    disconnect_players(srv);
}

void run_server(server_t *srv)
{
    int select_ret = 0;
    int i = 0;

    printf("Server started on port %zu\n", srv->args->port);
    while (!srv->close) {
        build_sets(srv, srv->cons);
        select_ret = select(get_max_fd(srv) + 1, srv->readfds,
            srv->writefds, NULL, NULL);
        if (select_ret < 0)
            return;
        if (FD_ISSET(srv->sock->fd, srv->readfds)) {
            accept_connection(srv);
            continue;
        }
        actions(srv);
    }
}
