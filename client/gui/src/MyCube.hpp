/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** MyCube
*/

#ifndef MYCUBE_HPP_
#define MYCUBE_HPP_

#include <iostream>
#include <vector>
#include <raylib-cpp.hpp>

class MyCube {
    public:
        MyCube();
        ~MyCube() = default;
        void draw();
        raylib::Vector3 getPosition() { return _position; }
        void setPosition(raylib::Vector3 position) { _position = position; }
        void setColor(raylib::Color color) { _color = color; }
        raylib::Color getColor() { return _color; }

    protected:
    private:
        raylib::Vector3 _position = {0.0f, 0.0f, 0.0f};
        raylib::Vector3 _size = {1.0f, 1.0f, 1.0f};
        raylib::Color _color = raylib::Color::Black();
};

#endif /* !MYCUBE_HPP_ */
