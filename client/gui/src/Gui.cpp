/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Gui
*/

#include "Gui.hpp"
#include "items/Item.hpp"

Gui::Gui() : _map(10, 10), _player()
{
    _width = 1920;
    _height = 1080;
}

void Gui::start()
{
    raylib::Window window(_width, _height, "Zappy");

    window.SetTargetFPS(60);
    //_map.initMap();
    while (!window.ShouldClose()) {
        _camera.updateCamera();
        window.BeginDrawing();
        window.ClearBackground(PURPLE);
        _camera.getCamera().BeginMode();
        //_map.draw();
        //_player.draw();
        _camera.getCamera().EndMode();
        window.DrawFPS(10, 10);
        window.EndDrawing();
    }
}
