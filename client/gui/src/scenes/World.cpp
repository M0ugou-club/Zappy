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
    for (int i = 0; i < (int)ItemRender::ItemType::COUNT; i++) {
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
            int x = std::stoi(args[0]);
            int y = std::stoi(args[1]);
            _map.setSize(x, y);
            for (auto &render : _itemRenders) {
                render->changeMapSize(_map.getSize());
            }
            for (int xdx = 0; xdx < x; xdx++) {
                for (int ydx = 0; ydx < y; ydx++) {
                    for (int i = 0; i < (int)ItemRender::ItemType::COUNT; i++) {
                        _items[std::make_tuple(xdx, ydx)][i] = 0;
                    }
                }
            }
        }},
        {"sgt (\\d+)$", [this](std::vector<std::string> args) {
            _timeUnit = std::stoi(args[0]);
        }},
        {"pnw #?(\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\w+)$", [this](std::vector<std::string> args) {
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
            _chat.sendMessage(args[0] + " starved to death", raylib::Color::Red());
        }},
        {"bct (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            raylib::Vector2 pos = {(float)std::stoi(args[0]), (float)std::stoi(args[1])};
            int items[(int)ItemRender::ItemType::COUNT];
            for (int i = 0; i < (int)ItemRender::ItemType::COUNT; i++) {
                items[i] = std::stoi(args[i + 2]);
            }
            for (int i = 0; i < (int)ItemRender::ItemType::COUNT; i++) {
                _items[std::make_tuple(pos.GetX(), pos.GetY())][i] = items[i];
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
            const int x = std::stoi(args[0]);
            const int y = std::stoi(args[1]);
            for (auto &player : _players) {
                if ((int)player.second->getPosition().GetX() == x && (int)player.second->getPosition().GetZ() == y) {
                    player.second->setIncantating(false);
                }
            }
        }},
        {"pgt #?(\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            raylib::Vector2 pos = {_players[std::stoi(args[0])]->getPosition().GetX(), _players[std::stoi(args[0])]->getPosition().GetZ()};
            _items[std::make_tuple((int)pos.GetX(), (int)pos.GetY())][std::stoi(args[1])]--;
        }},
        {"pdr #?(\\d+) (\\d+)$", [this](std::vector<std::string> args) {
            raylib::Vector2 pos = {_players[std::stoi(args[0])]->getPosition().GetX(), _players[std::stoi(args[0])]->getPosition().GetZ()};
            _items[std::make_tuple((int)pos.GetX(), (int)pos.GetY())][std::stoi(args[1])]++;
        }},
        {"pbc #?(\\d+) (.+)", [this](std::vector<std::string> args) {
            _chat.sendMessage(args[0] + ": " + args[1]);
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
    _chat.sendMessage("Welcome to Zappy", raylib::Color::Green());
    _chat.sendMessage("Map is " + std::to_string(static_cast<int>(_map.getSize().GetX())) + "x" +
        std::to_string(static_cast<int>(_map.getSize().GetY())));
    _chat.sendMessage("Here are the teams :");
    for (auto &team : _teams) {
        _chat.sendMessage((" - " + team), raylib::Color::White());
    }
}

void World::update()
{
    parseEventQueue();
    _camera.updateCamera();
    _window->BeginDrawing();
    _window->ClearBackground(raylib::Color::SkyBlue());
    _camera.getCamera().BeginMode();
    _map.draw();
    for (auto &player : _players) {
        player.second->draw();
    }
    drawItems();
    _camera.getCamera().EndMode();
    _chat.update();
    DrawFPS(10, 10);
    _window->EndDrawing();
}

void World::unload()
{
}
