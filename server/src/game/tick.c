/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tick
*/

#include "game.h"
#include "server.h"

static bool eat(server_t *srv, player_t *ply)
{
    connection_t *tmp = get_client_by_fd(srv->cons, ply->fd);

    if (tmp == NULL)
        return false;
    if (time_passed(&ply->eat_cooldown)) {
        if (ply->inventory[FOOD] > 0) {
            ply->inventory[FOOD] -= 1;
            set_cooldown(&ply->eat_cooldown, EAT_TIME / srv->args->frequency);
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
    if (time_passed(&ply->action_cooldown)) {
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
        if (!ply->disconnect)
            apply_incantation(srv, ply);
        ply = ply->next;
    }
}
