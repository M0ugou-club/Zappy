##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

SRC = 	src/map_size.c \
		src/tile_content.c \
		src/map_content.c \
		src/player_position.c \
		src/player_level.c \
		src/player_inventory.c \
		src/time_request.c \
		src/time_modification.c \
		src/forward.c \
		src/right.c \
		src/left.c \
		src/look.c \
		src/inventory.c \
		src/broadcast.c \
		src/connect_nbr.c \
		src/fork.c \
		src/eject.c \
		src/take_object.c \
		src/set_object.c \
		src/incantation.c

OBJ = $(SRC:.c=.o)

NAME = ipcshared.a


$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo -e "\033[0;32m[OK] \033[0m\033[0;36m$(NAME)\033[0m"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) "#*#"
	@$(RM) "*~"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g3
debug: re

.PHONY: all clean fclean re
