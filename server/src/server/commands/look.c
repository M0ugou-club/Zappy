/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/

#include "server.h"

// Look in a cone in front of the player
void cmd_look(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);
    char response[1024] = "";
    int cone_width = 3;

    for (int i = 1; i < player->level; i++) {
        cone_width += 2;
        for (int j = 0; j < cone_width; j++) {
        }
    }
}
