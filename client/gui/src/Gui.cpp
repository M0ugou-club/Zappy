/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Gui
*/

#include "Gui.hpp"

Gui::Gui()
{
    _width = 960;
    _height = 540;
    _camera = MyCamera();
    _map = Map(10, 10);
}

Gui::~Gui()
{
}

void Gui::start()
{
    raylib::Window window(_width, _height, "Zappy");
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);
    while (!window.ShouldClose()) {
        BeginDrawing();
        window.ClearBackground(RAYWHITE);
        BeginMode3D(_camera.get_camera());
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);
        EndMode3D();
        DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);
        DrawFPS(10, 10);
        EndDrawing();
    }
}
