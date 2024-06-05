/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Gui
*/

#include "Gui.hpp"
#include "items/Item.hpp"

Gui::Gui()
{
    _width = 1920;
    _height = 1080;
    _camera = MyCamera();
    _map = Map(10, 10);
}

Gui::~Gui()
{
}

void Gui::start()
{
    raylib::Window window(_width, _height, "Zappy");

    window.SetTargetFPS(60);
    _map.init_map();
    while (!window.ShouldClose()) {
        _camera.updateCamera();
        window.BeginDrawing();
        window.ClearBackground(PURPLE);
        _camera.getCamera().BeginMode();
        _map.draw();
        _camera.getCamera().EndMode();
        window.DrawFPS(10, 10);
        window.EndDrawing();
    }
}
