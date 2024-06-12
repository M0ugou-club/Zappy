/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include "AScene.hpp"
    #include "../ui/Button.hpp"
    #include <raylib-cpp.hpp>

class Menu : public AScene {
    public:
        Menu(const raylib::Window &window, std::string &newSceneName, std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> queues);
        ~Menu() = default;

        void load();
        void update();
        void unload();

    private:
        raylib::Camera2D _camera;
        std::shared_ptr<raylib::Window> _window;
        Button _playButton;
        Button _exitButton;
        std::string &_newSceneName;
};

#endif /* !MENU_HPP_ */
