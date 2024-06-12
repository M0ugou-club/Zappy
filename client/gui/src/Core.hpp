/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "Map.hpp"
    #include "MyCamera.hpp"
    #include "scenes/World.hpp"
    #include "scenes/Menu.hpp"
    #include "Args.hpp"
    #include <string>
    #include <map>
    #include <memory>
    #include <exception>

class Core {
    public:
        Core(const Args &args, SafeQueue<std::string> *eventQueue);
        ~Core() = default;
        void start();

        void loadScenes(raylib::Window &window);
        void loadScene(const std::string &scene);

    private:
        const Args &_args;
        int _width;
        int _height;
        const std::string _defaultScene;
        std::string _currentScene;
        std::map<std::string, std::unique_ptr<IScene>> _scenes;
        std::string _newSceneName;
        SafeQueue<std::string> *_eventQueue;
};

#endif /* !CORE_HPP_ */
