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
		src/server/broadcast_gui.c \
		src/server/close_server.c \
		src/game/player/add_player.c \
		src/game/player/remove_player.c \
		src/game/player/get_player_by_fd.c \
		src/game/player/new_player.c \
		src/game/player/disconnect_players.c \
		src/game/tick.c \
		src/game/team_exists.c \
		src/server/commands/broadcast.c \
		src/server/commands/connect_nbr.c \
		src/server/commands/eject.c \
		src/server/commands/fork.c \
		src/server/commands/incantation.c \
		src/server/commands/inventory.c \
		src/server/commands/item.c \
		src/server/commands/look.c \
		src/server/commands/move.c \
		src/server/commands/gui/bct.c \
		src/server/commands/gui/mct.c \
		src/server/commands/gui/msz.c \
		src/server/commands/gui/pin.c \
		src/server/commands/gui/plv.c \
		src/server/commands/gui/ppo.c \
		src/server/commands/gui/sgt.c \
		src/server/commands/gui/sst.c \
		src/server/commands/gui/tna.c \
		src/server/commands/other/pnw.c \
		src/server/commands/other/ebo.c \
		src/server/commands/other/edi.c \
		src/server/commands/other/enw.c \
		src/server/commands/other/pbc.c \
		src/server/commands/other/pdi.c \
		src/server/commands/other/pdr.c \
		src/server/commands/other/pex.c \
		src/server/commands/other/pfk.c \
		src/server/commands/other/pgt.c \
		src/server/commands/other/pic.c \
		src/server/commands/other/pie.c \
		src/server/commands/other/sbp.c \
		src/server/commands/other/seg.c \
		src/server/commands/other/smg.c \
		src/server/commands/other/suc.c \
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
