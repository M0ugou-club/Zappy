/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(std::string skin, const raylib::Vector2 &position, const raylib::Vector2 &size, const ColorsMap &colors, const std::string &text)
    : Panel(skin, position, size, colors), _text(text)
{
}

bool Button::hovered()
{
    return CheckCollisionPointRec(GetMousePosition(), _destRec);
}

bool Button::clicked()
{
    return hovered() && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

bool Button::justClicked()
{
    return _justClicked;
}

bool Button::justReleased()
{
    return _justReleased;
}

void Button::draw()
{
    if (!clicked() && _clicked) {
        _justReleased = true;
    } else {
        _justReleased = false;
    }
    if (clicked()) {
        if (!_clicked)
            _justClicked = true;
        else
            _justClicked = false;
        _clicked = true;
        Panel::draw("press");
    } else {
        _clicked = false;
        _justClicked = false;
        if (hovered())
            Panel::draw("hover");
        else
            Panel::draw();
    }
    raylib::DrawText(_text.c_str(), _position.x + _size.x / 2 - MeasureText(_text.c_str(), 20) / 2, _position.y + _size.y / 2 - 10, 20, _colorMap["text"]);
}