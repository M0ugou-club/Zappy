/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** item
*/

#include "server.h"

static get_val_from_object(char *str)
{
    char objects[7][10] = {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame"
    };

    for (int i = 0; i < 7; i++) {
        if (strcmp(str, objects[i]) == 0)
            return i;
    }
    return -1;
}

// Take an object from the ground
void cmd_take(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);
    char *item = strndup(parse->str + parse->pmatch[1].rm_so,
        parse->pmatch[1].rm_eo - parse->pmatch[1].rm_so);
    int object_val = get_val_from_object(item);

    if (object_val == -1) {
        queue_formatted_message(cl, "ko\n");
        free(item);
        return;
    }
    if (player->square->items[object_val] > 0) {
        player->square->items[object_val] -= 1;
        player->inventory[object_val] += 1;
        queue_formatted_message(cl, "ok\n");
    } else {
        queue_formatted_message(cl, "ko\n");
    }
    free(item);
}

// Put an object on the ground
void cmd_set(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);
    char *object = strndup(parse->str + parse->pmatch[1].rm_so,
        parse->pmatch[1].rm_eo - parse->pmatch[1].rm_so);
    int object_val = get_val_from_object(object);

    if (object_val == -1) {
        queue_formatted_message(cl, "ko\n");
        free(object);
        return;
    }
    if (player->inventory[object_val] > 0) {
        player->inventory[object_val] -= 1;
        player->square->items[object_val] += 1;
        queue_formatted_message(cl, "ok\n");
    } else {
        queue_formatted_message(cl, "ko\n");
    }

    free(object);
}
