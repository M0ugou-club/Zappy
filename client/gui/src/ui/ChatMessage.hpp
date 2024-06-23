/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** CharMessage
*/

#ifndef CHARMESSAGE_HPP_
    #define CHARMESSAGE_HPP_

    #include <raylib-cpp.hpp>
    #include <string>
    #include <iostream>

class ChatMessage {
    public:

        static constexpr int LIFE_TIME = 300;
        static constexpr int DECAY_TIME = 40;

        ChatMessage(raylib::Font *font, std::string message, raylib::Color color);
        ~ChatMessage();

        ChatMessage(const ChatMessage &other);

        void update(int pos);
        bool isAlive();

    private:
        std::string _message;
        raylib::Font *_font;

        raylib::Text _text;
        int _lifeTime = LIFE_TIME;
        int _decayTime = DECAY_TIME;
};

#endif /* !CHARMESSAGE_HPP_ */
