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

static void incantation_message(server_t *srv,
    connection_t *cl, player_t *player)
{
    player_t *tmp = srv->game->players;
    connection_t *t_cl = srv->cons;

    for (int i = 0; tmp != NULL; i++) {
        if (tmp->square == player->square) {
            t_cl = get_client_by_fd(srv->cons, tmp->fd);
            tmp->level++;
            queue_formatted_message(t_cl, "Current level: %d", tmp->level);
        }
        tmp = tmp->next;
    }
}

// Begin an incantation
void cmd_incantation(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);
    int i_inventory = 1;

    if (!check_incantation(srv, cl, player))
        return;
    queue_formatted_message(cl, "Elevation underway");
    for (int i = 0; i < 7; i++) {
        player->square->items[i_inventory] -=
            incantation[player->level - 1][i];
        i_inventory++;
    }
    incantation_message(srv, cl, player);
}
