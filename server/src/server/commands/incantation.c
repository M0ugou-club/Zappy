/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation
*/

#include "server.h"

static const int incantation[7][7] =
{
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

static bool enough_players(server_t *srv, player_t *ply)
{
    int players = 0;
    player_t *tmp = srv->game->players;

    while (tmp != NULL) {
        if (tmp->square == ply->square)
            players++;
        tmp = tmp->next;
    }
    return players >= incantation[ply->level - 1][0];
}

static void players_incantation(server_t *srv, player_t *ply)
{
    player_t *tmp = srv->game->players;

    while (tmp != NULL) {
        if (tmp->square == ply->square) {
            tmp->incantation = true;
            tmp->action_cooldown = get_time() +
                CALC_TIME(300.0f / srv->args->frequency);
        }
        tmp = tmp->next;
    }
}

static bool check_incantation(server_t *srv,
    connection_t *cl, player_t *player)
{
    int i_inventory = 1;

    if (player->level == 8 || !enough_players(srv, player)) {
        queue_formatted_message(cl, "ko\n");
        return false;
    }
    for (int i = 0; i < 7; i++) {
        if (player->square->items[i_inventory] <
            incantation[player->level - 1][i]) {
            queue_formatted_message(cl, "ko\n");
            return false;
        }
        i_inventory++;
    }
    return true;
}

void incantation_message(server_t *srv, connection_t *cl, player_t *ply)
{
    ply->level++;
    queue_formatted_message(cl, "Current level: %d\n", ply->level);
}

// Begin an incantation
void cmd_incantation(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);
    int i_inventory = 1;

    if (!check_incantation(srv, cl, player))
        return;
    for (int i = 0; i < 7; i++) {
        player->square->items[i_inventory] -=
            incantation[player->level - 1][i];
        i_inventory++;
    }
    player->incantation = true;
    players_incantation(srv, player);
    queue_formatted_message(cl, "Elevation underway\n");
}
