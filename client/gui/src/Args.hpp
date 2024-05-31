/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Args
*/

#ifndef ARGS_HPP_
#define ARGS_HPP_

#include <iostream>
#include <string>
#include <vector>

class Args {

    class BadArgumentException : public std::exception {
        public:
            BadArgumentException(const std::string &message) : _message(message) {}
            ~BadArgumentException() throw() {}
            const char *what() const throw() { return _message.c_str(); }

        private:
            std::string _message;
    };

    public:
        static int main_example(int ac, char **av);
        static bool isNumber(const std::string &str);

        Args(int ac, char **av);
        ~Args();

        int setArgs();
        std::string getIp() const;
        int getPort() const;

    private:
        void _processIp(int i);
        void _processPort(int i);

        int _ac;
        std::vector<std::string> _av;
        std::string _ip;
        int _port;
};

#endif /* !ARGS_HPP_ */
