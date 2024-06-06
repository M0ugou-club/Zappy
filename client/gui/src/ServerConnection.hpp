/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** ServerConnection
*/

#ifndef SERVER_CONNECTION_HPP_
    #define SERVER_CONNECTION_HPP_

    #include <iostream>
    #include <string>
    #include <memory>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

class ServerConnection {
    public:
        ServerConnection(std::string ip, int port);
        ~ServerConnection();

        void connectToServer();
        void disconnectFromServer();
        std::string tryReceive();

    private:
        std::string _ip;
        int _port;
        int _socket = -1;
        struct sockaddr_in _addr;
};

#endif /* !SERVER_HPP_ */
