/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** ServerConnection
*/

#include "ServerConnection.hpp"

ServerConnection::ServerConnection(std::string ip, int port, std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> queues)
    : _ip(ip), _port(port), _queues(queues)
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
    if (_socket == -1) {
        return;
    }
    _thread.join();
    close(_socket);
    _socket = -1;
}

std::string ServerConnection::tryReceive()
{
    char buffer[1024] = {0};
    memset(buffer, 0, 1024);
    int valread = read(_socket, buffer, 1024);
    if (valread == -1) {
        throw std::runtime_error("Error reading from server");
    }
    return std::string(buffer);
}

void ServerConnection::sendToServer(std::string msg)
{
    std::get<1>(_queues)->enqueue(msg);
}

int ServerConnection::_selectFd() {
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

void ServerConnection::_receiveLoop()
{
    int sel;
    sel = _selectFd();
    if (sel == 0) {
        return;
    }
    std::string msg = tryReceive();
    std::get<0>(_queues)->enqueue(msg);
    std::cout << "<- : " << msg << std::endl;
}

void ServerConnection::_sendLoop()
{
    std::string sending;

    while (std::get<1>(_queues)->empty()) {
        sending = std::get<1>(_queues)->dequeue();
        if (send(_socket, sending.c_str(), sending.length(), 0) == -1) {
            throw std::runtime_error("Error sending to server");
        }
        std::cout << "-> : " << sending << std::endl;
    }
}

void ServerConnection::connectToServerThread()
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
    while (true) {
        _receiveLoop();
        _sendLoop();
    }
}
