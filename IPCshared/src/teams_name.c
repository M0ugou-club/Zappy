/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** teams_name
*/

#include <unistd.h>
#include <string.h>

void teams_name(int serv_fd)
{
    write(serv_fd, "tna\n", strlen("tna") + 1);
}
