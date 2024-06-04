/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Gui
*/

#include "Gui.hpp"

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

    SetTargetFPS(60);
    _map.init_map();
    while (!window.ShouldClose()) {
        BeginDrawing();
        window.ClearBackground(PURPLE);
        BeginMode3D(_camera.get_camera());
        _map.draw();
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }
}
