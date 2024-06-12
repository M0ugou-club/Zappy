/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** World
*/

#ifndef WORLD_HPP_
    #define WORLD_HPP_

    #include <memory>
    #include <map>
    #include <regex>
    #include "AScene.hpp"
    #include "../Map.hpp"
    #include "../MyCamera.hpp"
    #include "World/Player.hpp"

class World : public AScene {
    public:
        World(const raylib::Window &window, std::string &newSceneName, SafeQueue<std::string> *eventQueue);
        ~World() = default;

        void load();
        void update();
        void unload();

        void parseEventQueue();
        void parsePacket(std::string packet);

        void addPlayer(std::string teamName, int id, int x, int y, int orientation, int level);

    private:
        MyCamera _camera;
        Map _map;
        std::map<raylib::Vector2, std::vector<int>> _items;
        std::string &_newSceneName;
        std::vector<std::string> _teams;
        std::map<int, std::unique_ptr<Player>> _players;
        int _timeUnit = 0;
};

#endif /* !WORLD_HPP_ */
