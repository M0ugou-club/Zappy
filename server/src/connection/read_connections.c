/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** read_connections
*/

#include "connection.h"
#include "server.h"

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
    player_t *ply = get_player_by_fd(srv->game->players, cli->fd);

    ret = read(cli->fd, tmp, BUFFER_SIZE);
    if (ret <= 0) {
        if (ply) {
            broadcast_gui(srv, "pdi %d\n", ply->id);
            remove_player(&srv->game->players, cli->fd);
        }
        remove_connection(&srv->cons, cli->fd);
        return true;
    }
    cli->buffer = append_buffer(cli->buffer, tmp, &cli->buffer_size, ret);
    return false;
}

static bool handshake(server_t *srv, char *team, connection_t *cl)
{
    if (strcmp(team, GRAPHIC_TEAM) == 0) {
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
    return false;
}

static char *get_team_ptr(server_t *srv, char *team)
{
    char *tmp = NULL;

    if (strcmp(team, GRAPHIC_TEAM) == 0)
        return GRAPHIC_TEAM;
    for (int i = 0; srv->game->teams[i]; i++) {
        if (strcmp(srv->game->teams[i], team) == 0) {
            tmp = srv->game->teams[i];
            break;
        }
    }
    return tmp;
}

static void read_team_internal(server_t *srv, char *tmp,
    connection_t *cli)
{
    player_t *ply = NULL;

    if (handshake(srv, tmp, cli)) {
        cli->handshake_step = ESTABLISHED;
        cli->team = get_team_ptr(srv, tmp);
        if (strcmp(cli->team, GRAPHIC_TEAM) == 0)
            return;
        if (check_eggs(srv->game, cli->team)) {
            ply = spawn_player(srv->game, cli->team, cli->fd);
            broadcast_gui(srv, "pnw #%zu %d %d %d %d %s\n",
                ply->id, ply->square->pos_x,
                ply->square->pos_y, ply->direction, ply->level,
                ply->team);
            return;
        }
    }
    send_formatted_message(cli, "ko\n");
    remove_connection(&srv->cons, cli->fd);
    return;
}

static void read_team(server_t *srv, connection_t *cli)
{
    ssize_t ret;
    char tmp[BUFFER_SIZE];

    memset(tmp, '\0', BUFFER_SIZE);
    ret = read(cli->fd, tmp, BUFFER_SIZE - 1);
    if (ret <= 0) {
        remove_connection(&srv->cons, cli->fd);
        return;
    }
    tmp[ret] = '\0';
    clean_str(tmp);
    read_team_internal(srv, tmp, cli);
}

void read_connections(server_t *srv)
{
    connection_t *tmp = srv->cons;
    bool ret = false;

    while (tmp != NULL) {
        if (tmp->handshake_step == TEAM && FD_ISSET(tmp->fd, srv->readfds)) {
            read_team(srv, tmp);
            return;
        }
        if (tmp->handshake_step == ESTABLISHED
            && FD_ISSET(tmp->fd, srv->readfds))
            ret = action(srv, tmp);
        if (ret)
            break;
        tmp = tmp->next;
    }
}
