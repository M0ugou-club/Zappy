/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look_helper
*/

#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *add_to_string(char *resp, char *li_cont)
{
    printf("resp ass: %s\n", resp);
    printf("li_cont ass: %s\n", li_cont);
    resp = realloc(resp, strlen(resp) + strlen(li_cont) + 1);
    strcat(resp, li_cont);
    printf("resultat du caca: %S\n", resp);
    return resp;
}

void add_vals(int *cone_width, int *cone_gap, int *cone_distance)
{
    *cone_width += 2;
    *cone_gap += 1;
    *cone_distance += 1;
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

cell_t *move_square_width(cell_t *square, direction_t orientation)
{
    if (orientation == NORTH)
        square = square->west;
    if (orientation == EAST)
        square = square->south;
    if (orientation == SOUTH)
        square = square->east;
    if (orientation == WEST)
        square = square->north;
    return square;
}
