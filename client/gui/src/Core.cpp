/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(const Args &args, SafeQueue<std::string> *eventQueue)
    : _args(args), _defaultScene("menu"), _eventQueue(eventQueue)
{
    _width = 1920 / 2;
    _height = 1080 / 2;
}

void Core::loadScenes(raylib::Window &window)
{
    _scenes["menu"] = std::make_unique<Menu>(window, _newSceneName, _eventQueue);
    _scenes["world"] = std::make_unique<World>(window, _newSceneName, _eventQueue);
}

void Core::loadScene(const std::string &scene)
{
    auto it = _scenes.find(scene);
    if (it == _scenes.end())
        throw std::runtime_error("Scene not found");
    it->second->load();
    if (_currentScene != "")
        _scenes[_currentScene]->unload();
    _currentScene = scene;
}

void Core::start()
{
    raylib::Window window(_width, _height, "Zappy");

    window.SetTargetFPS(60);
    loadScenes(window);
    loadScene(_defaultScene);
    while (!window.ShouldClose() && !_scenes[_currentScene]->shouldClose()) {
        _scenes[_currentScene]->update();
        if (_newSceneName != "") {
            loadScene(_newSceneName);
            _newSceneName = "";
        }
    }
}
