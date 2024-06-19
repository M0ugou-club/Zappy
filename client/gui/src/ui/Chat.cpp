/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Chat
*/

#include "Chat.hpp"

Chat::Chat()
    : _font("bonus/assets/fonts/pixel.ttf", (int)20, 0, 250)
{
    std::cout << "Font loaded : " << _font.IsReady() << std::endl;
}

Chat::~Chat()
{
}

void Chat::update()
{
    int i = 0;

    for (auto &message : _messages) {
        i++;
        message.update(i);
        if (!message.isAlive())
            _messages.erase(_messages.begin() + i - 1);
    }
}

void Chat::sendMessage(std::string message, raylib::Color color)
{
    if (_messages.size() >= 20)
        _messages.pop_back();
    _messages.insert(_messages.begin(), ChatMessage(&_font, message, color));
}
