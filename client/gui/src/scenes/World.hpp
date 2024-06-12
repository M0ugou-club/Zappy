/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** World
*/

#ifndef WORLD_HPP_
    #define WORLD_HPP_

    #include <memory>
    #include "AScene.hpp"
    #include "../Map.hpp"
    #include "../MyCamera.hpp"

class World : public AScene {
    public:
        World(const raylib::Window &window, std::string &newSceneName);
        ~World() = default;

        void load();
        void update();
        void unload();

    private:
        MyCamera _camera;
        Map _map;
        std::string &_newSceneName;
};

#endif /* !WORLD_HPP_ */
