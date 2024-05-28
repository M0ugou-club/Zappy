/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <stdlib.h>

typedef enum direction_e {
    NORTH,
    SOUTH,
    EAST,
    WEST
} direction_t;

typedef enum item_e {
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    FOOD,
    NONE
} item_t;

typedef struct square_s {
    item_t items[NONE];
    struct square_s *north;
    struct square_s *south;
    struct square_s *east;
    struct square_s *west;
} square_t;

typedef struct player_s {
    size_t id;
    char *team;
    struct square_s *square;
    direction_t direction;
    size_t level;
    item_t inventory[NONE];
} player_t;

typedef struct game_s {
    struct square_s *map;
    struct player_s *players;
    char **teams;
} game_t;

game_t *init_game(int x, int y, char **teams);
void free_game(game_t *game);

#endif /* !GAME_H_ */
