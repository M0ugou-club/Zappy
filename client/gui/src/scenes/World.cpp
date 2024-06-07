/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** World
*/

#include "World.hpp"

World::World(const raylib::Window &window, std::string &newSceneName)
    : _map(10, 10), _newSceneName(newSceneName)
{
    _window = std::make_shared<raylib::Window>(window);
}

void World::load()
{
    _map.initMap();
}

void World::update()
{
    _camera.updateCamera();
    _window->BeginDrawing();
    _window->ClearBackground(raylib::Color::Black());
    _camera.getCamera().BeginMode();
    _map.draw();
    _camera.getCamera().EndMode();
    _window->DrawFPS(10, 10);
    _window->EndDrawing();
}

void World::unload()
{
}
