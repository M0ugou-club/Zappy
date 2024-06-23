/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/

#include "server.h"

static const char *objects[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

static cell_t *go_forward(direction_t dir, cell_t *cell)
{
    switch (dir) {
        case NORTH:
            return cell->north;
        case EAST:
            return cell->east;
        case SOUTH:
            return cell->south;
        case WEST:
            return cell->west;
    }
    return cell;
}

static cell_t *go_left(direction_t dir, cell_t *cell)
{
    switch (dir) {
        case NORTH:
            return cell->west;
        case EAST:
            return cell->north;
        case SOUTH:
            return cell->east;
        case WEST:
            return cell->south;
    }
    return cell;
}

static cell_t *go_right(direction_t dir, cell_t *cell)
{
    switch (dir) {
        case NORTH:
            return cell->east;
        case EAST:
            return cell->south;
        case SOUTH:
            return cell->west;
        case WEST:
            return cell->north;
    }
    return cell;
}

static char *append_string(char *dst, const char *src)
{
    char *res = NULL;
    size_t dst_len = dst ? strlen(dst) : 0;

    res = malloc(dst_len + strlen(src) + 1);
    memset(res, 0, dst_len + strlen(src) + 1);
    if (dst)
        strcpy(res, dst);
    strcat(res, src);
    return res;
}

static char *append_object(char *dst, const char *object, size_t count)
{
    char *res = NULL;
    size_t dst_len = dst ? strlen(dst) : 0;

    res = malloc(dst_len + (strlen(object) * count) + count + 1);
    memset(res, 0, dst_len + (strlen(object) * count) + count + 1);
    if (dst)
        strcpy(res, dst);
    for (size_t i = 0; i < count; i++) {
        strcat(res, object);
        strcat(res, " ");
    }
    return res;
}

static char *get_contents(server_t *srv, cell_t *cell)
{
    char *res = NULL;
    size_t player_count = 0;

    for (player_t *ply = srv->game->players; ply; ply = ply->next)
        if (ply->square->pos_x == cell->pos_x &&
            ply->square->pos_y == cell->pos_y)
            player_count++;
    res = append_object(res, "player", player_count);
    for (size_t i = 0; i < NONE - 1; i++)
        res = append_object(res, objects[i], cell->items[i]);
    return res;
}

static char *do_cells(size_t j, size_t i, server_t *srv, player_t *ply)
{
    cell_t *cell = ply->square;
    char *res = NULL;

    for (size_t k = 0; k < j; k++)
        cell = go_forward(ply->direction, cell);
    for (size_t k = 0; k < i; k++)
        cell = go_left(ply->direction, cell);
    res = append_string(res, get_contents(srv, cell));
    if (i != ply->level || j != (i * 2))
        res = append_string(res, ",");
    return res;
}

void cmd_look(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *ply = get_player_by_fd(srv->game->players, cl->fd);
    size_t rows = ply->level;
    char *res = strdup("[");

    if (ply == NULL)
        return;
    for (size_t i = 0; i <= rows; i++)
        for (size_t j = 0; j < (i * 2) + 1; j++)
            res = append_string(res, do_cells(j, i, srv, ply));
    res = append_string(res, "]\n");
    queue_formatted_message(cl, res);
    free(res);
}
