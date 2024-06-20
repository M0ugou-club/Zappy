/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/

#include "server.h"

square_t *get_square_start(player_t *player, int cone_gap, int cone_distance)
{
    direction_t orientation = player->direction;
    square_t *square = player->square;

    for (int i = 0; i < cone_distance; i++) {
        if (square == NULL) {
            return NULL;
        }
        if (orientation == NORTH) {
            square = square->north;
        } else if (orientation == EAST) {
            square = square->east;
        } else if (orientation == SOUTH) {
            square = square->south;
        } else if (orientation == WEST) {
            square = square->west;
        }
    }
    for (int i = 0; i < cone_gap; i++) {
        if (square == NULL) {
            return NULL;
        }
        if (orientation == NORTH) {
            square = square->west;
        } else if (orientation == EAST) {
            square = square->north;
        } else if (orientation == SOUTH) {
            square = square->east;
        } else if (orientation == WEST) {
            square = square->south;
        }
    }
    return square;
}

char* get_square_content(square_t *square, server_t *srv)
{
    static char response[1024];
    strcpy(response, ""); // Reset the response buffer
    char objects[7][10] = {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame"
    };
    player_t *players = srv->game->players;
    int players_count = 0;

    while (players) {
        if (players->square == square) {
            players_count++;
        }
        players = players->next;
    }
    while (players_count > 0) {
        strcat(response, "player");
        if (players_count > 1) {
            strcat(response, " ");
        }
        players_count--;
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < square->items[i]; j++) {
            if (strlen(response) > 0) {
                strcat(response, " ");
            }
            strcat(response, objects[i]);
        }
    }
    return response;
}

char* get_lines_squares(player_t *player, int cone_width, square_t *square_start, server_t *srv)
{
    static char response[1024];
    direction_t orientation = player->direction;
    square_t *square = square_start;
    int width = cone_width;

    strcpy(response, "");
    for (int i = 0; i < width; i++) {
        if (square != NULL) {
            strcat(response, get_square_content(square, srv));
        }
        if (i != width - 1) {
            strcat(response, ",");
        }
        if (square != NULL) {
            if (orientation == NORTH) {
                square = square->east;
            } else if (orientation == EAST) {
                square = square->south;
            } else if (orientation == SOUTH) {
                square = square->west;
            } else if (orientation == WEST) {
                square = square->north;
            }
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