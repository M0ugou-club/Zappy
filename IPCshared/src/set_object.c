/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** set_object
*/

#include <unistd.h>
#include <string.h>

void set_object(int serv_fd, char *object)
{
    write(serv_fd, "Set ", strlen("Set "));
    write(serv_fd, object, strlen(object));
    write(serv_fd, "\n", 1);
}
