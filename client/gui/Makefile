##
## EPITECH PROJECT, 2024
## Zappy [WSL: Fedora]
## File description:
## Makefile
##

NAME = zappy_gui

SRC = gui.cpp \
		Args.cpp \

SRC := $(addprefix src/, $(SRC))

OBJ = $(SRC:.cpp=.o)

CXX = g++

COLOR_GREEN = \033[0;32m
COLOR_BLUE = \033[0;34m
COLOR_YELLOW = \033[0;33m
COLOR_RESET = \033[0m

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -lraylib

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
