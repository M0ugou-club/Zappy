/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_level
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void player_level(int serv_fd, int player_id)
{
    char *str = malloc(sizeof(char) * 10);

    sprintf(str, "plv %d\n", player_id);
    write(serv_fd, str, strlen(str));
}
