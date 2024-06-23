/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <stdlib.h>
    #include <time.h>
    #include <stdbool.h>
    #include <string.h>

    #define EAT_TIME 126.0f
    #define INCANTATION_TIME 300.0f
    #define REFILL_TIME 20.0f

typedef enum direction_e {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
} direction_t;

typedef enum item_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NONE
} item_t;

typedef struct max_items_s {
    int items[NONE];
} max_items_t;

typedef struct egg_s {
    char *team;
    size_t id;
} egg_t;

typedef struct cell_s {
    egg_t **eggs;
    unsigned int items[NONE];
    int pos_x;
    int pos_y;
    bool updated;
    struct cell_s *north;
    struct cell_s *south;
    struct cell_s *east;
    struct cell_s *west;
} cell_t;

typedef struct player_s {
    size_t id;
    char *team;
    cell_t *square;
    direction_t direction;
    struct timeval action_cooldown;
    size_t level;
    unsigned int inventory[NONE];
    int fd;
    struct timeval eat_cooldown;
    bool disconnect;
    bool incantation;
    struct player_s *next;
} player_t;

typedef struct game_s {
    int map_x;
    int map_y;
    max_items_t *max_items;
    cell_t **map;
    player_t *players;
    struct timeval refill_cooldown;
    int max_players;
    char **teams;
    int *team_slots;
} game_t;

void add_egg(cell_t *square, char *team_name);
void del_egg(cell_t *square, char *team_name);
bool check_egg(cell_t *square, char *team_name);
bool check_eggs(game_t *game, char *team_name);

void free_game(game_t *game);
max_items_t *fill_density(int x, int y);
bool team_exists(char **teams, char *team);

player_t *new_player(char *team_name);
player_t *add_player(player_t *player, player_t *new_player);
void remove_player(player_t **players, int sockfd);
player_t *spawn_player(game_t *game, char *team, int fd);

#endif /* !GAME_H_ */
