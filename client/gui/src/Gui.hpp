/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include <iostream>
#include <raylib/raylib-cpp.hpp>
#include "Map.hpp"
#include "Camera.hpp"

class Gui {
    public:
        Gui();
        ~Gui();
        void start();

    protected:
    private:
        int _width;
        int _height;
        Camera _camera;
        Map _map;
};

#endif /* !GUI_HPP_ */
