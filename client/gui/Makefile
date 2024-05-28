##
## EPITECH PROJECT, 2024
## Zappy [WSL: Fedora]
## File description:
## Makefile
##

NAME = zappy_gui

SRC = gui.cpp

SRC := $(addprefix src/, $(SRC))

CXX = g++

COLOR_GREEN = \033[0;32m
COLOR_BLUE = \033[0;34m
COLOR_YELLOW = \033[0;33m
COLOR_RESET = \033[0m

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -lraylib

all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC)
	@echo -e "$(COLOR_GREEN)[OK] $(COLOR_GREEN)$(NAME) compiled$(COLOR_RESET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo -e "$(COLOR_GREEN)[OK] $(COLOR_YELLOW)$@$(COLOR_RESET)"

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += -g
debug: re

.PHONY: all clean fclean re
