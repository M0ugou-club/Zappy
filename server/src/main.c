/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include <stdio.h>
#include "server.h"
#include "game.h"

int main(int argc, char **argv)
{
    server_t *server = NULL;
    game_t *game = NULL;

    game = init_game(10, 10, NULL);
    place_items_randomly(game);
    for (int i = 0; i < game->map_x; i++) {
        for (int j = 0; j < game->map_y; j++) {
            printf("Square (%d, %d): food=%d, linemate=%d, deraumere=%d, sibur=%d, mendiane=%d, phiras=%d, thystame=%d\n",
                   i, j,
                   game->map[i][j].food,
                   game->map[i][j].linemate,
                   game->map[i][j].deraumere,
                   game->map[i][j].sibur,
                   game->map[i][j].mendiane,
                   game->map[i][j].phiras,
                   game->map[i][j].thystame);
        }
    }
    int cmpt_food = 0;
    for (int i = 0; i < game->map_x; i++) {
        for (int j = 0; j < game->map_y; j++) {
            cmpt_food += game->map[i][j].food;
        }
    }
    printf("Total food: %d\n", cmpt_food);
    int cmpt_linemate = 0;
    for (int i = 0; i < game->map_x; i++) {
        for (int j = 0; j < game->map_y; j++) {
            cmpt_linemate += game->map[i][j].linemate;
        }
    }
    printf("Total linemate: %d\n", cmpt_linemate);
    int cmpt_phiras = 0;
    for (int i = 0; i < game->map_x; i++) {
        for (int j = 0; j < game->map_y; j++) {
            cmpt_phiras += game->map[i][j].phiras;
        }
    }
    printf("Total phiras: %d\n", cmpt_phiras);
    return EXIT_SUCCESS;
}
