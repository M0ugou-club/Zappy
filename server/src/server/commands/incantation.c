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

static bool check_incantation(server_t *srv,
    connection_t *cl, player_t *player)
{
    int i_inventory = 1;

    if (player->level == 8) {
        queue_formatted_message(cl, "ko");
        return false;
    }
    for (int i = 0; i < 7; i++) {
        if (player->inventory[i_inventory] <
            incantation[player->level - 1][i]) {
            queue_formatted_message(cl, "ko");
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

    queue_formatted_message(cl, "Current level: %d", player->level);
    for (int i = 0; tmp != NULL; i++) {
        if (tmp->square == player->square && tmp->fd != cl->fd) {
            t_cl = get_client_by_fd(srv->cons, tmp->fd);
            queue_formatted_message(t_cl, "Current level: %d", player->level);
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
        player->inventory[i_inventory] -= incantation[player->level - 1][i];
    }
    player->level += 1;
    incantation_message(srv, cl, player);
}
