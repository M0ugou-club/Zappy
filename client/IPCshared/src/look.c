/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/

#include <unistd.h>
#include <string.h>

void look(int serv_fd)
{
    write(serv_fd, "Look\n", strlen("Look") + 1);
}
