/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_size
*/

#include <unistd.h>
#include <string.h>

void map_size(int serv_fd)
{
    write(serv_fd, "msz\n", strlen("msz") + 1);
}
