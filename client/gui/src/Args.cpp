/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Args
*/

#include "Args.hpp"
#include "ServerConnection.hpp"

#include <memory>

bool Args::isNumber(const std::string &str)
{
    for (const auto &c : str) {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

Args::Args(int ac, char **av)
    : _ac(ac), _av(std::vector<std::string>(av, av + ac))
{
}

int Args::setArgs()
{
    if (_av.size() < 5) {
        throw std::runtime_error("Not enough arguments");
    } else if (_av.size() > 5) {
        throw std::runtime_error("Too many arguments");
    }
    for (int i = 1; i < _ac; i++) {
        if (_av[i][0] != '-')
            continue;
        if (_av[i] == "-p") {
            _processPort(i + 1);
        } else if (_av[i] == "-h") {
            _processIp(i + 1);
        } else {
            throw std::runtime_error("Invalid arguments");
        }
    }
    return 0;
}

std::string Args::getIp() const
{
    return _ip;
}

int Args::getPort() const
{
    return _port;
}

void Args::_processIp(int i)
{
    _ip = _av[i];
}

void Args::_processPort(int i)
{
    if (Args::isNumber(_av[i]) == false) {
        throw std::runtime_error("Invalid port");
    }
    try {
        _port = std::stoi(_av[i]);
    } catch (std::exception &e) {
        throw std::runtime_error("Invalid port");
    }
}
