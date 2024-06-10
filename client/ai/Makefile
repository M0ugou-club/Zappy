##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

PYTHON = python

SRC = 	src/player.py \
		src/connexion.py \

DIST_DIR = dist

BUILD_DIR = build

NAME = zappy_ai

$(NAME): $(MAIN_SCRIPT)
	pyinstaller --onefile --name $(NAME) $(SRC)
	mv $(DIST_DIR)/$(NAME) $(NAME)

clean:
	rm -rf $(DIST_DIR) $(BUILD_DIR) $(NAME).spec

fclean:
	rm -rf $(DIST_DIR) $(BUILD_DIR) $(NAME).spec
	rm -f $(NAME)

all: clean build run

re: fclean all

.PHONY: clean fclean all re
