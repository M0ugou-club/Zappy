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
		src/server/run_server.c \
		src/server/get_client_by_fd.c \
		src/server/build_sets.c \
		src/server/execute_connections.c \
		src/server/send_message.c \
		src/server/send_messages.c \
		src/server/queue_message.c \
		src/args/get_args.c \
		src/args/free_args.c \
		src/args/set/set_port.c \
		src/args/set/set_size.c \
		src/args/set/set_game_properties.c \
		src/args/error_args.c \
		src/game/egg.c \
		src/game/init_game.c \
		src/game/free_game.c \
		src/game/fill_map.c \
		src/socket/init_socket.c \
		src/socket/free_socket.c \
		src/connection/add_connection.c \
		src/connection/free_connection.c \
		src/connection/new_connection.c \
		src/connection/remove_connection.c \
		src/connection/read_connections.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include

$(NAME): $(OBJ)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	@gcc $(CFLAGS) -o $@ -c $<
	@echo -e "\033[0;32m[OK] \033[0m\033[0;36m$<\033[0m"

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
