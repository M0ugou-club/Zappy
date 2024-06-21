/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Chat
*/

#ifndef CHAT_HPP_
    #define CHAT_HPP_

    #include <raylib-cpp.hpp>

    #include "ChatMessage.hpp"

class Chat {
    public:
        Chat();
        ~Chat();

        void update();
        void sendMessage(std::string message, raylib::Color color = raylib::Color::White());

    private:
        std::vector<ChatMessage> _messages;
        raylib::Font _font;
};

#endif /* !CHAT_HPP_ */
