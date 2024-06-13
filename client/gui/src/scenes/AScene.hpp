/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AScene
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_

    #include "IScene.hpp"
    #include "Window.hpp"
    #include "../SafeQueue.hpp"
    #include <string>
    #include <memory>
    #include <tuple>

class AScene : public IScene {
    public:
        virtual ~AScene() = default;

        virtual void load() = 0;
        virtual void update() = 0;
        virtual void unload() = 0;

        void closeWindow();
        bool shouldClose() { return _shouldClose; }

    protected:
        std::shared_ptr<raylib::Window> _window;
        std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> _queues;
        bool _shouldClose = false;
};

#endif /* !ASCENE_HPP_ */
