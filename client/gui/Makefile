##
## EPITECH PROJECT, 2024
## Zappy [WSL: Fedora]
## File description:
## Makefile
##

NAME = zappy_gui

SRC = main.cpp \
	  Core.cpp \
	  Args.cpp \
	  ServerConnection.cpp \
	  Map.cpp \
	  MyCamera.cpp \
	  MyCube.cpp \
	  ui/ColorsMap.cpp \
	  ui/Panel.cpp \
	  ui/Button.cpp \
	  ui/Chat.cpp \
	  ui/ChatMessage.cpp \
	  scenes/AScene.cpp \
	  scenes/Menu.cpp \
	  scenes/World.cpp \
	  scenes/World/ItemRender.cpp \
	  scenes/World/Player.cpp \

SRC := $(addprefix src/, $(SRC))

OBJ = $(SRC:.cpp=.o)

CXX = g++

COLOR_GREEN = \033[0;32m
COLOR_BLUE = \033[0;34m
COLOR_YELLOW = \033[0;33m
COLOR_RESET = \033[0m

CXXFLAGS = -Wall -Wextra -std=c++20\
	$(shell uname -m | grep -q "arm" && echo "--start-no-unused-arguments"\
        && echo "-I/opt/homebrew/Cellar/raylib/5.0/include"\
        && echo "-L/opt/homebrew/Cellar/raylib/5.0/lib" || echo "")\
		-I./raylib-cpp/include/ -lraylib

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@echo -e "$(COLOR_GREEN)[OK] $(COLOR_YELLOW)$(NAME) $(COLOR_BLUE)"\
		" compiled$(COLOR_RESET)"

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo -e "$(COLOR_GREEN)[OK] $(COLOR_BLUE)$< $(COLOR_RESET)"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += -g
debug: re

.PHONY: all clean fclean re
