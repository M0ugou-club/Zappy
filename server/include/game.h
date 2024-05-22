/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

typedef enum ore_e {
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NONE
} ore_t;

typedef struct square_s {
    ore_t minerals[NONE];
    struct square_s *north;
    struct square_s *south;
    struct square_s *east;
    struct square_s *west;
} square_t;

typedef struct game_s {
    square_t squares[];
} game_t;

#endif /* !GAME_H_ */
