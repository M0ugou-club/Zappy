/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** read_connections
*/

#include "connection.h"
#include "server.h"

static bool action_setup(connection_t *conn)
{
    if (conn == NULL)
        return true;
    if (conn->buffer == NULL) {
        conn->buffer = malloc(BUFFER_SIZE);
        if (conn->buffer == NULL)
            return true;
        memset(conn->buffer, 0, BUFFER_SIZE);
    } else {
        conn->buffer = realloc(conn->buffer,
            sizeof(conn->buffer) + BUFFER_SIZE);
        if (conn->buffer == NULL)
            return true;
    }
    return false;
}

static int strcount(const char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        count += str[i] == c;
    return count;
}

static bool action(server_t *srv, connection_t *cli)
{
    char tmp[BUFFER_SIZE];
    ssize_t ret;

    if (action_setup(cli))
        return false;
    ret = read(cli->fd, tmp, BUFFER_SIZE - 1);
    if (ret <= 0) {
        remove_connection(&srv->cons, cli->fd);
        return true;
    }
    tmp[ret] = '\0';
    memcpy(cli->buffer + strlen(cli->buffer), tmp, ret);
    return false;
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
    SEND_FD(cl->fd, "ko\n");
    return false;
}

static bool read_team(server_t *srv, connection_t *cli)
{
    ssize_t ret;
    char tmp[BUFFER_SIZE];

    memset(tmp, '\0', BUFFER_SIZE);
    ret = read(cli->fd, tmp, BUFFER_SIZE - 1);
    if (ret <= 0) {
        remove_connection(&srv->cons, cli->fd);
        return true;
    }
    tmp[ret] = '\0';
    clean_str(tmp);
    if (handshake(srv, tmp, cli)) {
        cli->handshake_step = ESTABLISHED;
        cli->team = strdup(tmp);
        return true;
    }
    remove_connection(&srv->cons, cli->fd);
    return false;
}

void read_connections(server_t *srv)
{
    connection_t *tmp = srv->cons;
    bool ret = false;

    while (tmp != NULL) {
        if (tmp->handshake_step == TEAM && FD_ISSET(tmp->fd, srv->readfds))
            ret = read_team(srv, tmp);
        if (!ret && tmp->handshake_step == ESTABLISHED && FD_ISSET(tmp->fd, srv->readfds))
            ret = action(srv, tmp);
        if (ret)
            break;
        tmp = tmp->next;
    }
}
