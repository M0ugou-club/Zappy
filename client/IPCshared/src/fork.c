/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fork
*/

#include <unistd.h>
#include <string.h>

void fork_player(int serv_fd)
{
    write(serv_fd, "Fork\n", strlen("Fork") + 1);
}
