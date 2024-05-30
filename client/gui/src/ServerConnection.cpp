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
}

void ServerConnection::disconnectFromServer()
{
    if (_socket != -1) {
        close(_socket);
        _socket = -1;
    }
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
