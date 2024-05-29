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
    fill_map(game);
    int cmpt_food = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 ; j++) {
            cmpt_food += game->map[i][j].food;
        }
    }
    printf("food: %d\n", cmpt_food);
    return EXIT_SUCCESS;
}
