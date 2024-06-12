/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** World
*/

#include "World.hpp"

World::World(const raylib::Window &window, std::string &newSceneName, SafeQueue<std::string> *eventQueue)
    : _map(10, 10), _newSceneName(newSceneName)
{
    _window = std::make_shared<raylib::Window>(window);
    _eventQueue = eventQueue;
}

void World::parseEventQueue()
{
    while (!_eventQueue->empty()) {
        std::string packet = _eventQueue->dequeue();
        parsePacket(packet);
    }

}

void World::parsePacket(std::string packet)
{
    const std::map<std::string, std::function<void(std::vector<std::string>)>> commands = {
        {"msz (\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            _map.setSize(std::stoi(args[0]), std::stoi(args[1]));
        }},
        {"sgt (\\d+)$", [this](std::vector<std::string> args) {
            _timeUnit = std::stoi(args[0]);
        }},
        {"pnw (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\w+)$", [this](std::vector<std::string> args) {
            addPlayer(args[5], std::stoi(args[0]), std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]), std::stoi(args[4]));
        }}
    };

    for (auto &command : commands) {
        std::regex regex(command.first);
        std::smatch match;
        if (std::regex_search(packet, match, regex)) {
            std::vector<std::string> args;
            for (unsigned long i = 1; i < match.size(); i++) {
                args.push_back(match[i]);
            }
            command.second(args);
            return;
        }
    }
}

void World::addPlayer(std::string teamName, int id, int x, int y, int orientation, int level)
{
    int teamIndex = 0;

    for (unsigned long i = 0; i < _teams.size(); i++) {
        if (_teams[i] == teamName) {
            teamIndex = i;
            break;
        }
    }
    _players[id] = std::make_unique<Player>(Player(teamIndex, _map.getSize()));
    _players[id]->setPosition({(float)x, (float)y, 0});
    _players[id]->setOrientation(orientation);
    _players[id]->setLevel(level);
}

void World::load()
{
    // read map size (msz)
    // read time unit (sgt)
    // read map contents (bct)
    // read teams (tna)

    _map.initMap();
}

void World::update()
{
    parseEventQueue();
    _camera.updateCamera();
    _window->BeginDrawing();
    _window->ClearBackground(raylib::Color::Black());
    _camera.getCamera().BeginMode();
    _map.draw();
    for (auto &player : _players) {
        player.second->draw();
    }
    _camera.getCamera().EndMode();
    _window->EndDrawing();
}

void World::unload()
{
}
