/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tile_content
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void tile_content(int serv_fd, int x, int y)
{
    char *str = malloc(sizeof(char) * 10);

    sprintf(str, "bct %d %d\n", x, y);
    write(serv_fd, str, strlen(str));
}
