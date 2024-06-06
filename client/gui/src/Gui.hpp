/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include "Map.hpp"
#include "MyCamera.hpp"
#include "Player.hpp"

class Gui {
    public:
        Gui();
        ~Gui() = default;
        void start();

    protected:
    private:
        int _width;
        int _height;
        MyCamera _camera;
        Map _map;
        Player _player;

};

#endif /* !GUI_HPP_ */
