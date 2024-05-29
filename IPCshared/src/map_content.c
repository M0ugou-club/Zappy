/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_content
*/

#include <unistd.h>
#include <string.h>

void map_content(int serv_fd)
{
    write(serv_fd, "mct\n", strlen("mct") + 1);
}
