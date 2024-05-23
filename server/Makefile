##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME = zappy_server

SRC =	src/main.c \
		src/server/init_server.c \
		src/server/free_server.c \
		src/game/init_game.c \
		src/game/free_game.c \
		src/socket/init_socket.c \
		src/socket/free_socket.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include

$(NAME): $(OBJ)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	@gcc $(CFLAGS) -o $@ -c $<

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
