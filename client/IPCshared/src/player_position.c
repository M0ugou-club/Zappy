/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_position
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void player_position(int serv_fd, int player_id)
{
    char *str = malloc(sizeof(char) * 10);

    sprintf(str, "ppo %d\n", player_id);
    write(serv_fd, str, strlen(str));
}
