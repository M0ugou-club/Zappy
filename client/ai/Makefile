##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME = zappy_ai

SRC = src/player.py \
	  src/connexion.py

$(NAME):
	touch $(NAME)
	echo "#!/bin/bash" >> $(NAME)
	/bin/echo -n "/usr/bin/env python3 $(SRC) $$" >> $(NAME)
	echo "@" >> $(NAME)
	chmod +x $(NAME)

all: $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
