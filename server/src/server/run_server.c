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

static bool handshake(server_t *srv, char *team, connection_t *cl)
{
    if (strcmp(team, "GRAPHIC") == 0) {
        queue_formatted_message(cl,
            "msz %zu %zu\n", srv->args->x, srv->args->y);
        queue_formatted_message(cl, "sgt %zu\n", srv->args->frequency);
        mct(srv, cl);
        tna(srv, cl);
        for (player_t *tmp = srv->game->players;
            tmp != NULL; tmp = tmp->next) {
            pnw(srv, cl, tmp);
        }
        return true;
    }
    if (team_exists(srv->game->teams, team)) {
        queue_formatted_message(cl, "%d\n", 1);
        queue_formatted_message(cl, " %d %d\n", srv->args->x, srv->args->y);
        return true;
    }
    send_formatted_message(cl, "ko\n", 0);
    return false;
}

static void clean_str(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n')
            str[i] = '\0';
        if (str[i] == '\r')
            str[i] = '\0';
    }
}

static bool handle_handshake(server_t *srv, connection_t *new)
{
    char *buffer = malloc(sizeof(char) * 1024);
    bool success = false;

    memset(buffer, '\0', 1024);
    read(new->fd, buffer, 1024);
    clean_str(buffer);
    if (handshake(srv, buffer, new)) {
        srv->cons = add_connection(srv->cons, new);
        success = true;
    } else {
        close(new->fd);
        free_connection(new);
    }
    free(buffer);
    return success;
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
    SEND_FD(newsockfd, "WELCOME\n");
    if (!handle_handshake(srv, new))
        return;
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

void run_server(server_t *srv)
{
    int select_ret = 0;

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
        read_connections(srv);
        execute_connections(srv);
        game_tick(srv);
        send_messages(srv);
        disconnect_players(srv);
    }
}
