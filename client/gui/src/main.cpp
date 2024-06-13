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
    std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> queues;
    std::get<IN>(queues) = new SafeQueue<std::string>;
    std::get<OUT>(queues) = new SafeQueue<std::string>;
    Core core(args, queues);

    try {
        args.setArgs();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./zappy_gui -p port -h machine" << std::endl;
        return 84;
    }

    ServerConnection server(args.getIp(), args.getPort(), queues);
    try {
        server.connectToServer();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 84;
    }
    server.sendToServer("GRAPHIC");

    core.start();
    server.disconnectFromServer();
    delete std::get<IN>(queues);
    delete std::get<OUT>(queues);
    return 0;
}
