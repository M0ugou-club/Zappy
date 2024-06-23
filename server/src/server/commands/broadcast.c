/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** broadcast
*/

#include "server.h"


int calculate_coordinate(int coord1, int coord2, int max_coord)
{
    int wrapped_dist1 = (coord2 - coord1 + max_coord) % max_coord;
    int wrapped_dist2 = (coord1 - coord2 + max_coord) % max_coord;

    return (wrapped_dist1 < wrapped_dist2) ? wrapped_dist1 : -wrapped_dist2;
}

static int map_direction_north(int dx, int dy)
{
    if (dx == 0 && dy == 0)
        return 0;
    if (dx == 0 && dy < 0)
        return 1;
    if (dx > 0 && dy < 0)
        return 2;
    if (dx > 0 && dy == 0)
        return 3;
    if (dx > 0 && dy > 0)
        return 4;
    if (dx == 0 && dy > 0)
        return 5;
    if (dx < 0 && dy > 0)
        return 6;
    if (dx < 0 && dy == 0)
        return 7;
    if (dx < 0 && dy < 0)
        return 8;
    return -1;
}

static int map_direction_east(int dx, int dy)
{
    if (dx == 0 && dy == 0)
        return 0;
    if (dx > 0 && dy == 0)
        return 1;
    if (dx > 0 && dy > 0)
        return 2;
    if (dx == 0 && dy > 0)
        return 3;
    if (dx < 0 && dy > 0)
        return 4;
    if (dx < 0 && dy == 0)
        return 5;
    if (dx < 0 && dy < 0)
        return 6;
    if (dx == 0 && dy < 0)
        return 7;
    if (dx > 0 && dy < 0)
        return 8;
    return -1;
}

static int map_direction_south(int dx, int dy)
{
    if (dx == 0 && dy == 0)
        return 0;
    if (dx == 0 && dy > 0)
        return 1;
    if (dx < 0 && dy > 0)
        return 2;
    if (dx < 0 && dy == 0)
        return 3;
    if (dx < 0 && dy < 0)
        return 4;
    if (dx == 0 && dy < 0)
        return 5;
    if (dx > 0 && dy < 0)
        return 6;
    if (dx > 0 && dy == 0)
        return 7;
    if (dx > 0 && dy > 0)
        return 8;
    return -1;
}

static int map_direction_west(int dx, int dy)
{
    if (dx == 0 && dy == 0)
        return 0;
    if (dx < 0 && dy == 0)
        return 1;
    if (dx < 0 && dy < 0)
        return 2;
    if (dx == 0 && dy < 0)
        return 3;
    if (dx > 0 && dy < 0)
        return 4;
    if (dx > 0 && dy == 0)
        return 5;
    if (dx > 0 && dy > 0)
        return 6;
    if (dx == 0 && dy > 0)
        return 7;
    if (dx < 0 && dy > 0)
        return 8;
    return -1;
}

int map_direction_based_on_orientation(int dx, int dy, direction_t direction)
{
    switch (direction) {
        case NORTH:
            return map_direction_north(dx, dy);
        case EAST:
            return map_direction_east(dx, dy);
            break;
        case SOUTH:
            return map_direction_south(dx, dy);
            break;
        case WEST:
            return map_direction_west(dx, dy);
            break;
    }
    return -1;
}

int get_direction(player_t *player, player_t *player_connected, game_t *game)
{
    int pos_x_rec = player->square->pos_x;
    int pos_y_rec = player->square->pos_y;
    int pos_x_sender = player_connected->square->pos_x;
    int pos_y_sender = player_connected->square->pos_y;
    int grid_width = game->map_x;
    int grid_height = game->map_y;
    int dx = calculate_coordinate(pos_x_rec, pos_x_sender, grid_width);
    int dy = calculate_coordinate(pos_y_rec, pos_y_sender, grid_height);
    int dir = 0;

    dir = map_direction_based_on_orientation(dx, dy, player->direction);
    return dir;
}

static void send_msg(server_t *srv, player_t *player, char *object, int dir)
{
    connection_t *conn = get_client_by_fd(srv->cons, player->fd);

    if (conn == NULL)
        return;
    queue_formatted_message(conn, "message %s, %d\n", object, dir);
}

// Send a message to everyone connected
void cmd_broadcast(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    game_t *game = srv->game;
    player_t *player = game->players;
    player_t *player_connected = get_player_by_fd(game->players, cl->fd);
    int direction = 0;
    char *object = strndup(parse->str + parse->pmatch[1].rm_so,
        parse->pmatch[1].rm_eo - parse->pmatch[1].rm_so);

    if (player == NULL) {
        free(object);
        return;
    }
    while (player != NULL) {
        direction = get_direction(player, player_connected, game);
        if (player->fd != cl->fd) {
            send_msg(srv, player, object, direction);
        }
        player = player->next;
    }
    broadcast_gui(srv, "pbc #%d %s\n", player->id, object);
    free(object);
}
