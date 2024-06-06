/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take_object
*/

#include <unistd.h>
#include <string.h>

void take_object(int serv_fd, char *object)
{
    write(serv_fd, "Take ", strlen("Take "));
    write(serv_fd, object, strlen(object));
    write(serv_fd, "\n", 1);
}
