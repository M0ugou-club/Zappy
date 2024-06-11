/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** inventory
*/

#include "server.h"

// Send the contents of the player's inventory
void cmd_inventory(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);

    queue_formatted_message(cl,
        "food = %d\nlinemate = %d\nderaumere = %d\nsibur "\
        "= %d\nmendiane = %d\nphiras = %d\nthystame = %d",
        player->inventory[0],
        player->inventory[1],
        player->inventory[2],
        player->inventory[3],
        player->inventory[4],
        player->inventory[5],
        player->inventory[6]);
}
