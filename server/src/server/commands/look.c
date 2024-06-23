/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/
#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
            square = square->west;
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

static void append_items(char **resp, int item_count, const char *item_name)
{
    for (int j = 0; j < item_count; j++) {
        if (strlen(*resp) > 0) {
            *resp = realloc(*resp, strlen(*resp) + strlen(" ") + 1);
            strcat(*resp, " ");
        }
        *resp = realloc(*resp, strlen(*resp) + strlen(item_name) + 1);
        strcat(*resp, item_name);
    }
}

static char *get_square_content(cell_t *square, server_t *srv)
{
    char *resp = malloc(1);
    int players_count = count_players_on_square(square, srv);

    *resp = '\0';
    while (players_count > 0) {
        resp = realloc(resp, strlen(resp) + strlen("player") + 1);
        strcat(resp, "player");
        if (players_count > 1) {
            resp = realloc(resp, strlen(resp) + strlen(" ") + 1);
            strcat(resp, " ");
        }
        players_count--;
    }
    for (int i = 0; i < 7; i++) {
        append_items(&resp, square->items[i], objects[i]);
    }
    return resp;
}

char *append_square_content(char *resp, cell_t *square, server_t *srv)
{
    char *sq_tent = get_square_content(square, srv);

    resp = realloc(resp, strlen(resp) + strlen(sq_tent) + 1);
    strcat(resp, sq_tent);
    free(sq_tent);
    return resp;
}

char *get_ln_squa(player_t *p, int cn_width, cell_t *sq_start, server_t *srv)
{
    char *resp = malloc(1);
    direction_t orientation = p->direction;
    cell_t *square = sq_start;

    *resp = '\0';
    for (int i = 0; i < cn_width; i++) {
        if (square != NULL) {
            resp = append_square_content(resp, square, srv);
        }
        if (i != cn_width - 1) {
            resp = add_to_string(resp, ",");
        }
        if (square != NULL) {
            square = move_square_width(square, orientation);
        }
    }
    return resp;
}

char *begin_response(char *resp, cell_t *square, server_t *srv)
{
    char *sq_cont = get_square_content(square, srv);

    printf("sq_cont: %s\n", sq_cont);
    resp = realloc(resp, strlen(resp) + strlen(sq_cont) + 1);
    strcat(resp, sq_cont);
    free(sq_cont);
    return resp;
}

char *look(server_t *srv, connection_t *cl, player_t *player, char *resp)
{
    int cone_width = 3;
    int cone_gap = 1;
    int cone_distance = 1;
    cell_t *start_line = NULL;
    char *li_cont = NULL;

    resp = begin_response(resp, player->square, srv);
    printf("resp: %s\n", resp);
    for (int i = 1; i <= player->level; i++) {
        start_line = get_start(player, cone_gap, cone_distance);
        add_to_string(resp, ",");
        printf("resp2: %s\n", resp);
        if (start_line != NULL) {
            li_cont = get_ln_squa(player, cone_width, start_line, srv);
            resp = add_to_string(resp, li_cont);
            printf("resp3: %s\n", resp);
            free(li_cont);
        }
        add_vals(&cone_width, &cone_gap, &cone_distance);
    }
    resp = add_to_string(resp, "]\n");
    return resp;
}

void cmd_look(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);
    char *resp = NULL;

    if (player == NULL)
        return;
    resp = malloc(2 * sizeof(char));
    resp = strcpy(resp, "[");
    resp = look(srv, cl, player, resp);
    queue_formatted_message(cl, resp);
    free(resp);
}
