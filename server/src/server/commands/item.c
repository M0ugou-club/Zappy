/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** item
*/

#include "server.h"

// Take an object from the ground
void cmd_take(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);

    for (int i = 0; i < 7; i++) {
        if (player->square->items[i] > 0) {
            player->inventory[i] += 1;
            player->square->items[i] -= 1;
        } else {
            queue_formatted_message(cl, "ko");
            return;
        }
    }
    queue_formatted_message(cl, "ok");
}

// Put an object on the ground
void cmd_set(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);

    for (int i = 0; i < 7; i++) {
        if (player->inventory[i] > 0) {
            player->inventory[i] -= 1;
            player->square->items[i] += 1;
        } else {
            queue_formatted_message(cl, "ko");
            return;
        }
    }
    queue_formatted_message(cl, "ok");
}
