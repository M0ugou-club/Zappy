/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** main
*/

#include "Core.hpp"
#include "Args.hpp"
#include "ServerConnection.hpp"

int main(int ac, char **av)
{
    Args args(ac, av);
    SafeQueue<std::string> queue;
    Core core(args, &queue);

    try {
        args.setArgs();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./zappy_gui -p port -h machine" << std::endl;
        return 84;
    }

    ServerConnection server(args.getIp(), args.getPort(), &queue);
    server.connectToServer();

    core.start();
    return 0;
}
