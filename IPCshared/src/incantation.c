/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation
*/

#include <unistd.h>
#include <string.h>

void incantation(int serv_fd)
{
    write(serv_fd, "Incantation\n", strlen("Incantation") + 1);
}
