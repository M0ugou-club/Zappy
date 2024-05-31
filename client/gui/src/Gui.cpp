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
}

Gui::~Gui()
{
}

void Gui::start()
{
    raylib::Window window(_width, _height, "Zappy");

    SetTargetFPS(60);
    while (!window.ShouldClose()) {
        BeginDrawing();
        window.ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
}
