/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Scene
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include <string>

class IScene {
    public:
        virtual ~IScene() = default;

        virtual void load() = 0;
        virtual void update() = 0;
        virtual void unload() = 0;

        virtual void closeWindow() = 0;
        virtual bool shouldClose() = 0;
};

#endif /* !ASCENE_HPP_ */
