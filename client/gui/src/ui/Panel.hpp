/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Panel
*/

#ifndef PANEL_HPP_
    #define PANEL_HPP_

    #include <map>
    #include "ColorsMap.hpp"
    #include "raylib-cpp.hpp"

class Panel {
    public:
        Panel(std::string skin, const raylib::Vector2 &position, const raylib::Vector2 &size, const ColorsMap &colors);
        ~Panel();

        void draw(std::string color = "default");

    protected:
        std::string _skin;
        raylib::Vector2 _position;
        raylib::Vector2 _size;
        ColorsMap _colorMap;

        raylib::Texture2D _sprite;
        raylib::Rectangle _sourceRec;
        raylib::Rectangle _destRec;
        NPatchInfo _npatchInfo;
};

#endif /* !PANEL_HPP_ */
