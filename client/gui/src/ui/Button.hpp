/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include "Panel.hpp"

class Button : public Panel {
    public:
        Button(std::string skin, const raylib::Vector2 &position, const raylib::Vector2 &size, const ColorsMap &colors, const std::string &text);
        ~Button() = default;

        void draw();
        bool clicked();
        bool justClicked();
        bool justReleased();
        bool hovered();

    private:
        std::string _text;
        bool _clicked;
        bool _justClicked;
        bool _justReleased;
};

#endif /* !BUTTON_HPP_ */
