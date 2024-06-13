/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#include "Menu.hpp"
#include "World.hpp"

Menu::Menu(const raylib::Window &window, std::string &newSceneName, std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> queues)
    : _playButton(
        "button.png",
        {(float)window.GetWidth() / 2 - 120, 250},
        {240, 50},
        ColorsMap::defaultColors(),
        "Play"
    ), _exitButton(
        "button.png",
        {(float)window.GetWidth() / 2 - 120, 325},
        {240, 50},
        ColorsMap::defaultColors(),
        "Exit"
    ),
    _newSceneName(newSceneName)
{
    _window = std::make_shared<raylib::Window>(window);
    _queues = queues;
}

void Menu::load()
{
    _camera = raylib::Camera2D({0, 0}, {0, 0}, 0, 1);
}

static void DrawOutlinedText(const char *text, int posX, int posY, int fontSize, Color color, int outlineSize, Color outlineColor) {
    raylib::DrawText(text, posX - outlineSize, posY - outlineSize, fontSize, outlineColor);
    raylib::DrawText(text, posX + outlineSize, posY - outlineSize, fontSize, outlineColor);
    raylib::DrawText(text, posX - outlineSize, posY + outlineSize, fontSize, outlineColor);
    raylib::DrawText(text, posX + outlineSize, posY + outlineSize, fontSize, outlineColor);
    raylib::DrawText(text, posX, posY, fontSize, color);
}

void Menu::update()
{
    _window->BeginDrawing();
    _window->ClearBackground(raylib::Color::SkyBlue());
    _camera.BeginMode();
    DrawOutlinedText("Zappy", _window->GetWidth() / 2 - raylib::MeasureText("Zappy", 128) / 2, 20, 128, raylib::Color::White(), 4, raylib::Color::Black());
    _playButton.draw();
    _exitButton.draw();
    if (_exitButton.justReleased())
        closeWindow();
    if (_playButton.justReleased())
        _newSceneName = "world";
    _camera.EndMode();
    _window->EndDrawing();
}

void Menu::unload()
{
}
