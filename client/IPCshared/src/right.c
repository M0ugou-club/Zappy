/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** right
*/

#include <unistd.h>
#include <string.h>

void right(int serv_fd)
{
    write(serv_fd, "Right\n", strlen("Right") + 1);
}
