/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation
*/

#include "server.h"

static const int incantation[7][6] =
{
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

// Begin an incantation
void cmd_incantation(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);
    player_t *tmp = srv->game->players;
    connection_t *tmp_cl = srv->cons;
    int i_inventory = 1;

    if (player->level == 8) {
        queue_formatted_message(cl, "ko");
        return;
    }
    for (int i = 0; i < 7; i++) {
        if (player->inventory[i_inventory] < incantation[player->level - 1][i]) {
            queue_formatted_message(cl, "ko");
            return;
        }
        i_inventory++;
    }
    i_inventory = 1;
    queue_formatted_message(cl, "Elevation underway");
    for (int i = 0; i < 7; i++) {
        player->inventory[i_inventory] -= incantation[player->level - 1][i];
    }
    player->level += 1;
    queue_formatted_message(cl, "Current level: %d", player->level);
    for (int i = 0; tmp != NULL; i++) {
        if (tmp->square == player->square && tmp->fd != cl->fd) {
            tmp_cl = get_client_by_fd(srv->cons, tmp->fd);
            queue_formatted_message(tmp_cl, "Current level: %d", player->level);
        }
        tmp = tmp->next;
    }
}
