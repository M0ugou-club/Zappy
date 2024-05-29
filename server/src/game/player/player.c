/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** player
*/

#include "game.h"
#include "player.h"

player_t *init_players(int max_players)
{
    player_t *players = malloc(sizeof(player_t) * max_players);

    if (players == NULL) {
        return NULL;
    }
    for (int i = 0; i < max_players; i++) {
        players[i].id = 0;
    }
    players[max_players - 1].id = -1;
    return players;
}

player_t *add_player(player_t *players, int id, char *team)
{
    int i = 0;

    while (players[i].id != 0) {
        i++;
    }
    players[i].id = id;
    players[i].team = team;
    players[i].square = NULL;
    players[i].direction = NORTH;
    players[i].level = 1;
    for (int j = 0; j < NONE; j++) {
        players[i].inventory[j] = 0;
    }
    return players;
}

player_t pop_player(player_t *players, int id)
{
    int i = 0;
    int j = 0;

    while (players[i].id != id) {
        i++;
    }
    players[i].id = 0;
    for (j = i + 1; players[j].id != -1; j++) {
        players[j - 1] = players[j];
    }
    players[j - 1].id = -1;

    return players[i];
}

player_t *get_player_by_id(player_t *players, int id)
{
    int i = 0;

    while (players[i].id != id) {
        i++;
    }
    return &players[i];
}

int get_player_count(player_t *players)
{
    int i = 0;

    while (players[i].id != 0) {
        i++;
    }
    return i;
}
