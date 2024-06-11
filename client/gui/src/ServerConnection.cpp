/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** ServerConnection
*/

#include "ServerConnection.hpp"

ServerConnection::ServerConnection(std::string ip, int port)
    : _ip(ip), _port(port)
{
}

ServerConnection::~ServerConnection()
{
    disconnectFromServer();
}

void ServerConnection::connectToServer()
{
    _thread = std::thread(&ServerConnection::connectToServerThread, this);
}

void ServerConnection::disconnectFromServer()
{
    _thread.join();
    close(_socket);
    _socket = -1;
}

std::string ServerConnection::tryReceive()
{
    char buffer[1024] = {0};
    int valread = read(_socket, buffer, 1024);
    if (valread == -1) {
        throw std::runtime_error("Error reading from server");
    }
    return std::string(buffer);
}

int ServerConnection::selectFd() {
    fd_set readfds;
    int retval;

    FD_ZERO(&readfds);
    FD_SET(_socket, &readfds);
    retval = select(_socket + 1, &readfds, NULL, NULL, NULL);
    if (retval == -1) {
        throw std::runtime_error("Error selecting socket");
    }
    return retval;
}

void ServerConnection::connectToServerThread()
{
    int sel;

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        throw std::runtime_error("Error creating socket");
    }
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = inet_addr(_ip.c_str());
    if (connect(_socket, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        throw std::runtime_error("Error connecting to server");
    }
    while (1) {
        sel = selectFd();
        if (sel == 0) {
            continue;
        }
        std::string msg = tryReceive();
        std::cout << msg << std::endl;
    }
}
