/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** ChatMessage
*/

#include "ChatMessage.hpp"

ChatMessage::ChatMessage(raylib::Font *font, std::string message, raylib::Color color)
    : _font(font), _text(*font, message, 20, 2, color)
{
}

ChatMessage::~ChatMessage()
{
}

void ChatMessage::update(int pos)
{
    int x = 0;
    int y = GetRenderHeight() - (60 + (20 * pos));
    if (_lifeTime == 0)
        _decayTime--;
    else
        _lifeTime--;
    if (_decayTime < 0)
        _decayTime = 0;
    DrawRectangle(x, y, 600, 20, {0, 0, 0, (unsigned char)(100 * _decayTime / DECAY_TIME)});
    _text.SetColor(raylib::Color(_text.color.r, _text.color.g, _text.color.b, 255 * _decayTime / DECAY_TIME));
    _text.Draw((raylib::Vector2){x + 5, y + 1});
}

bool ChatMessage::isAlive()
{
    return _decayTime > 0;
}
