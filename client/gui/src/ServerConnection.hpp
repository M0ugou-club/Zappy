/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** ServerConnection
*/

#ifndef SERVER_CONNECTION_HPP_
    #define SERVER_CONNECTION_HPP_

    #include "Defines.hpp"
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
    #include <atomic>

class ServerConnection {
    public:
        ServerConnection(std::string ip, int port, std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> queues);
        ~ServerConnection();

        void connectToServer();
        void disconnectFromServer();
        std::string tryReceive();
        void sendToServer(std::string msg, std::string endWith = "\n");


    private:
        void _serverLoop();
        int _selectFd();
        void _receiveLoop();
        void _sendLoop();

        std::string _ip;
        int _port;
        std::atomic<bool> _connected = false;
        std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> _queues;
        std::thread _thread;
        int _fd = -1;
        fd_set _readfds;
        struct sockaddr_in _addr;
};

#endif /* !SERVER_HPP_ */
