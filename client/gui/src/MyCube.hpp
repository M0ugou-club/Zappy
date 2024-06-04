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
#include <raylib/raylib-cpp.hpp>

class MyCube {
    public:
        MyCube();
        ~MyCube();
        void draw();
        Vector3 get_position() { return _position; }
        void set_position(Vector3 position) { _position = position; }
        void set_color(raylib::Color color) { _color = color; }

    protected:
    private:
        Vector3 _position = {0.0f, 0.0f, 0.0f};
        Vector3 _size = {1.0f, 1.0f, 1.0f};
        raylib::Color _color = raylib::Color::Black();
};

#endif /* !MYCUBE_HPP_ */
