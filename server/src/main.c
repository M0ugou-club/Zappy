/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "server.h"

static int usage(int exit_code)
{
    printf("USAGE: ./zappy_server -p port -x width -y height");
    printf(" -n name1 name2 ... -c clientsNb -f freq\n");
    return exit_code;
}

int main(int argc, char **argv)
{
    server_t *server = NULL;
    args_t *args = get_args(argc, argv);

    srand(time(NULL));
    if (args == NULL)
        return usage(EXIT_ERROR);
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
        return usage(EXIT_SUCCESS);
    if (error_args(args))
        return usage(EXIT_ERROR);
    server = init_server(args);
    if (server == NULL) {
        dprintf(2, "Error: Server could not be initialized\n");
        return EXIT_ERROR;
    }
    run_server(server);
    free_server(server);
    free_args(args);
    return EXIT_SUCCESS;
}
