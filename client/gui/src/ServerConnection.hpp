/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** ServerConnection
*/

#ifndef SERVER_CONNECTION_HPP_
    #define SERVER_CONNECTION_HPP_

    #include "SafeQueue.hpp"

    #include <iostream>
    #include <string>
    #include <memory>
    #include <thread>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <cstring>

class ServerConnection {
    public:
        ServerConnection(std::string ip, int port, std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> queues);
        ~ServerConnection();

        void connectToServer();
        void disconnectFromServer();
        std::string tryReceive();
        void sendToServer(std::string msg);

        void connectToServerThread();

    private:
        int _selectFd();
        void _receiveLoop();
        void _sendLoop();

        std::string _ip;
        int _port;
        std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> _queues;
        std::thread _thread;
        int _socket = -1;
        struct sockaddr_in _addr;
};

#endif /* !SERVER_HPP_ */
