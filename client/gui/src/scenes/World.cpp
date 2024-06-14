/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** World
*/

#include "World.hpp"

World::World(const raylib::Window &window, std::string &newSceneName, std::tuple<SafeQueue<std::string> *, SafeQueue<std::string> *> queues)
    : _map(2, 2), _newSceneName(newSceneName)
{
    _window = std::make_shared<raylib::Window>(window);
    _queues = queues;
    for (int i = 0; (ItemRender::ItemType)i < ItemRender::ItemType::COUNT; i++) {
        _itemRenders.push_back(std::make_unique<ItemRender>((ItemRender::ItemType)i, 0));
    }
}

void World::parseEventQueue()
{
    while (!std::get<IN>(_queues)->empty()) {
        std::string packet = std::get<IN>(_queues)->dequeue();
        parsePacket(packet);
    }

}

void World::parsePacket(std::string packet)
{
    const std::map<std::string, std::function<void(std::vector<std::string>)>> commands = {
        {"msz (\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            _map.setSize(std::stoi(args[0]), std::stoi(args[1]));
            for (auto &render : _itemRenders) {
                render->changeMapSize(_map.getSize());
            }
        }},
        {"sgt (\\d+)$", [this](std::vector<std::string> args) {
            _timeUnit = std::stoi(args[0]);
        }},
        {"pnw (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\w+)$", [this](std::vector<std::string> args) {
            addPlayer(args[5], std::stoi(args[0]), std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]), std::stoi(args[4]));
        }},
        {"ppo #?(\\d+) (\\d+) (\\d+) ([1-4])$", [this](std::vector<std::string> args) {
            _players[std::stoi(args[0])]->setPosition({(float)std::stoi(args[1]), 0, (float)std::stoi(args[2])});
            _players[std::stoi(args[0])]->setOrientation(std::stoi(args[3]));
        }},
        {"plv #?(\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            _players[std::stoi(args[0])]->setLevel(std::stoi(args[1]));
        }},
        {"tna (\\w+)$", [this](std::vector<std::string> args) {
            _teams.push_back(args[0]);
        }},
        {"pdi #?(\\d+)$", [this](std::vector<std::string> args) {
            removePlayer(std::stoi(args[0]));
        }},
        {"bct (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            raylib::Vector2 pos = {(float)std::stoi(args[0]), (float)std::stoi(args[1])};
            int items[(int)ItemRender::ItemType::COUNT];
            for (int i = 0; i < (int)ItemRender::ItemType::COUNT; i++) {
                items[i] = std::stoi(args[i + 2]);
            }
            for (int i = 0; i < (int)ItemRender::ItemType::COUNT; i++) {
                _items[std::make_tuple(pos.GetX(), pos.GetY())].push_back(items[i]);
            }
        }},
        {"pic (\\d+) (\\d+) (\\d+) ([#0-9 ]+)$", [this](std::vector<std::string> args) {
            std::cout << "Incantation started" << std::endl;
            std::string search = args[3];
            std::vector<std::string> players;
            std::regex playerRegex = std::regex("#?(\\d+)");
            std::smatch match;
            while (std::regex_search(search, match, playerRegex)) {
                players.push_back(match[1]);
                search = match.suffix();
            }
            for (auto &player : players) {
                std::cout << "Player " << player << " is incantating" << std::endl;
                _players[std::stoi(player)]->setIncantating(true);
            }
        }},
        {"pie (\\d+) (\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            for (auto &player : _players) {
                player.second->setIncantating(false);
            }
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

void World::drawItems()
{
    for (auto &item : _items) {
        for (int i = 0; i < (int)ItemRender::ItemType::COUNT; i++) {
            if (item.second[i] > 0) {
                _itemRenders[i]->draw({std::get<0>(item.first), std::get<1>(item.first)}, item.second[i]);
            }
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
    _players[id] = std::make_unique<Player>(teamIndex, _map.getSize());
    _players[id]->setPosition({(float)x, 0, (float)y});
    _players[id]->setOrientation(orientation);
    _players[id]->setLevel(level);
}


void World::removePlayer(int id)
{
    _players.erase(id);
}

void World::load()
{
    parseEventQueue();
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
    drawItems();
    _camera.getCamera().EndMode();
    DrawFPS(10, 10);
    _window->EndDrawing();
}

void World::unload()
{
}
