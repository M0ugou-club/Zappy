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
    "thystame"
    };

static square_t *move_square_distance(square_t *square, direction_t orientation, int distance)
{
    for (int i = 0; i < distance; i++) {
        if (orientation == NORTH) {
            square = square->north;
        }
        if (orientation == EAST) {
            square = square->east;
        }
        if (orientation == SOUTH) {
            square = square->south;
        }
        if (orientation == WEST) {
            square = square->west;
        }
    }
    return square;
}

static square_t *move_square_gap(square_t *square, direction_t orientation, int gap)
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

static square_t *get_square_start(player_t *player, int cone_gap, int cone_distance)
{
    direction_t orientation = player->direction;
    square_t *square = player->square;

    square = move_square_distance(square, orientation, cone_distance);
    square = move_square_gap(square, orientation, cone_gap);
    return square;
}

int count_players_on_square(square_t *square, server_t *srv) {
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

static void append_items_of_type(char *response, int item_count, const char *item_name) {
    for (int j = 0; j < item_count; j++) {
        if (strlen(response) > 0) {
            strcat(response, " ");
        }
        strcat(response, item_name);
    }
}

char* get_square_content(square_t *square, server_t *srv) {
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
        append_items_of_type(response, square->items[i], objects[i]);
    }
    return response;
}

static square_t *move_square_widht(square_t *square, direction_t orientation)
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

char* get_lines_squares(player_t *player, int cone_width, square_t *square_start, server_t *srv)
{
    static char response[1024];
    direction_t orientation = player->direction;
    square_t *square = square_start;

    strcpy(response, "");
    for (int i = 0; i < cone_width; i++) {
        if (square != NULL)
            strcat(response, get_square_content(square, srv));
        if (i != cone_width - 1)
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

    strcpy(response, "[");
    strcat(response, get_square_content(player->square, srv));
    for (int i = 1; i <= player->level; i++) {
        square_t *start_line = get_square_start(player, cone_gap, cone_distance);
        strcat(response, ",");
        if (start_line != NULL) {
            strcat(response, get_lines_squares(player, cone_width, start_line, srv));
        }
        cone_width += 2;
        cone_gap += 1;
        cone_distance += 1;
    }
    strcat(response, "]\n");
    queue_formatted_message(cl, response);
}