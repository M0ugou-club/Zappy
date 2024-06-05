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
        if(IsKeyDown(KEY_W))
            _camera.moveCamera(_camera.FORWARD);
        if(IsKeyDown(KEY_S))
            _camera.moveCamera(_camera.BACKWARD);
        if(IsKeyDown(KEY_A))
            _camera.moveCamera(_camera.LEFT);
        if(IsKeyDown(KEY_D))
            _camera.moveCamera(_camera.RIGHT);
        window.BeginDrawing();
        window.ClearBackground(PURPLE);
        _camera.getCamera().BeginMode();
        _map.draw();
        _camera.getCamera().EndMode();
        window.DrawFPS(10, 10);
        window.EndDrawing();
    }
}
