/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tick
*/

#include "server.h"

static bool eat(server_t *srv, player_t *ply)
{
    connection_t *tmp = get_client_by_fd(srv->cons, ply->fd);

    if (tmp == NULL)
        return false;
    if (difftime(time(NULL), ply->last_eat)
        >= EAT_TIME / srv->args->frequency) {
        if (ply->inventory[FOOD] > 0) {
            ply->inventory[FOOD] -= 1;
            ply->last_eat = time(NULL);
            return true;
        } else {
            send_formatted_message(tmp, "dead\n");
            return false;
        }
    }
    return true;
}

void apply_incantation(server_t *srv, player_t *ply)
{
    connection_t *cl = get_client_by_fd(srv->cons, ply->fd);

    if (!ply->incantation)
        return;
    if (difftime(time(NULL), ply->last_action)
        >= 300.0f / srv->args->frequency) {
        ply->incantation = false;
        incantation_message(srv, cl, ply);
    }
}

void game_tick(server_t *srv)
{
    player_t *ply = srv->game->players;

    srv->game->tick++;
    while (ply != NULL) {
        ply->disconnect = !eat(srv, ply);
        apply_incantation(srv, ply);
        ply = ply->next;
    }
}
