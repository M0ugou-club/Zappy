/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_inventory
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void player_inventory(int serv_fd, int player_id)
{
    char *str = malloc(sizeof(char) * 10);

    sprintf(str, "pin %d\n", player_id);
    write(serv_fd, str, strlen(str));
}
