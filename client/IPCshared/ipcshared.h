/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ipcshared
*/

#ifndef IPC_SHARED_H_
    #define IPC_SHARED_H_

void map_size(int serv_fd);

void tile_content(int serv_fd, int x, int y);
void map_content(int serv_fd);
void teams_name(int serv_fd);
void player_position(int serv_fd, int player_id);
void player_level(int serv_fd, int player_id);
void player_inventory(int serv_fd, int player_id);
void time_request(int serv_fd);
void time_modification(int serv_fd, int time);
void forward(int serv_fd);
void right(int serv_fd);
void left(int serv_fd);
void look(int serv_fd);
void inventory(int serv_fd);
void broadcast(int serv_fd, char *message);
void connect_nbr(int serv_fd);
void fork_player(int serv_fd);
void eject(int serv_fd);
void take_object(int serv_fd, char *object);
void set_object(int serv_fd, char *object);
void incantation(int serv_fd);

#endif /* !IPC_SHARED_H_ */
