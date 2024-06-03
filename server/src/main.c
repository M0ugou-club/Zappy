/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "server.h"

int main(int argc, char **argv)
{
    server_t *server = NULL;
    args_t *args = get_args(argc, argv);

    if (args == NULL)
        return EXIT_ERROR;
    server = init_server(args);
    if (server == NULL)
        return EXIT_ERROR;
    run_server(server);
    free_server(server);
    free_args(args);
    return EXIT_SUCCESS;
}
