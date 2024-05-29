/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** inventory
*/

#include <unistd.h>
#include <string.h>

void inventory(int serv_fd)
{
    write(serv_fd, "Inventory\n", strlen("Inventory") + 1);
}
