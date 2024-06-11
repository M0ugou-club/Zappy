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
    #include <string>
    #include <map>
    #include <memory>
    #include <exception>

class Core {
    public:
        Core();
        ~Core() = default;
        void start();

        void loadScenes(raylib::Window &window);
        void loadScene(const std::string &scene);

    protected:
    private:
        int _width;
        int _height;
        const std::string _defaultScene;
        std::string _currentScene;
        std::map<std::string, std::unique_ptr<IScene>> _scenes;
        std::string _newSceneName;
};

#endif /* !CORE_HPP_ */