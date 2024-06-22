/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/

#include "server.h"

const char *objects[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"};

static cell_t *mv_distance(cell_t *square, direction_t ori, int distance)
{
    for (int i = 0; i < distance; i++) {
        if (ori == NORTH) {
            square = square->north;
        }
        if (ori == EAST) {
            square = square->east;
        }
        if (ori == SOUTH) {
            square = square->south;
        }
        if (ori == WEST) {
            square = square->west;
        }
    }
    return square;
}

static cell_t *mv_gap(cell_t *square, direction_t orientation, int gap)
{
    for (int i = 0; i < gap; i++) {
        if (orientation == NORTH) {
            square = square->west;
        }
        if (orientation == EAST) {
            square = square->north;
        }
        if (orientation == SOUTH) {
            square = square->east;
        }
        if (orientation == WEST) {
            square = square->south;
        }
    }
    return square;
}

static cell_t *get_start(player_t *player, int cone_gap, int cone_distance)
{
    direction_t orientation = player->direction;
    cell_t *square = player->square;

    square = mv_distance(square, orientation, cone_distance);
    square = mv_gap(square, orientation, cone_gap);
    return square;
}

int count_players_on_square(cell_t *square, server_t *srv)
{
    player_t *players = srv->game->players;
    int players_count = 0;

    while (players) {
        if (players->square == square) {
            players_count++;
        }
        players = players->next;
    }
    return players_count;
}

static void append_items(char *response, int item_count, const char *item_name)
{
    for (int j = 0; j < item_count; j++) {
        if (strlen(response) > 0) {
            strcat(response, " ");
        }
        strcat(response, item_name);
    }
}

char *get_square_content(cell_t *square, server_t *srv)
{
    static char response[1024];
    int players_count = count_players_on_square(square, srv);

    strcpy(response, "");
    while (players_count > 0) {
        strcat(response, "player");
        if (players_count > 1) {
            strcat(response, " ");
        }
        players_count--;
    }
    for (int i = 0; i < 7; i++) {
        append_items(response, square->items[i], objects[i]);
    }
    return response;
}

static cell_t *move_square_widht(cell_t *square, direction_t orientation)
{
    if (orientation == NORTH)
        square = square->west;
    if (orientation == EAST)
        square = square->north;
    if (orientation == SOUTH)
        square = square->east;
    if (orientation == WEST)
        square = square->south;
    return square;
}

char *get_ln_squa(player_t *p, int cn_width, cell_t *sq_start, server_t *srv)
{
    static char response[1024];
    direction_t orientation = p->direction;
    cell_t *square = sq_start;

    strcpy(response, "");
    for (int i = 0; i < cn_width; i++) {
        if (square != NULL)
            strcat(response, get_square_content(square, srv));
        if (i != cn_width - 1)
            strcat(response, ",");
        if (square != NULL) {
            square = move_square_widht(square, orientation);
        }
    }
    return response;
}

void cmd_look(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);
    static char response[1024];
    int cone_width = 3;
    int cone_gap = 1;
    int cone_distance = 1;
    cell_t *start_line = NULL;

    strcpy(response, "[");
    strcat(response, get_square_content(player->square, srv));
    for (int i = 1; i <= player->level; i++) {
        start_line = get_start(player, cone_gap, cone_distance);
        strcat(response, ",");
        if (start_line != NULL)
            strcat(response, get_ln_squa(player, cone_width, start_line, srv));
        cone_width += 2;
        cone_gap += 1;
        cone_distance += 1;
    }
    strcat(response, "]\n");
    queue_formatted_message(cl, response);
}
