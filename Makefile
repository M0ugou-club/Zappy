##
## EPITECH PROJECT, 2024
## Zappy [WSL: Fedora]
## File description:
## Makefile
##

NAME_SERVER = zappy_server
NAME_AI = zappy_ai
NAME_GUI = zappy_gui

COLOR_GREEN = \033[0;32m
COLOR_BLUE = \033[0;34m
COLOR_RESET = \033[0m

all: $(NAME_SERVER) $(NAME_AI) $(NAME_GUI)

server:
	$(MAKE) -C server
	mv server/$(NAME_SERVER) .
	@echo -e "$(COLOR_GREEN)[OK] $(NAME_SERVER) moved to root directory$(COLOR_RESET)"

ai:
	$(MAKE) -C ai
	mv ai/$(NAME_AI) .
	@echo -e "$(COLOR_GREEN)[OK] $(NAME_AI) moved to root directory$(COLOR_RESET)"

gui:
	$(MAKE) -C gui
	mv gui/$(NAME_GUI) .
	@echo -e "$(COLOR_GREEN)[OK] $(NAME_GUI) moved to root directory$(COLOR_RESET)"


clean:
	$(MAKE) -C server clean
	$(MAKE) -C ai clean
	$(MAKE) -C gui clean

fclean:
	$(MAKE) -C server fclean
	$(MAKE) -C ai fclean
	$(MAKE) -C gui fclean
	rm -f $(NAME_SERVER) $(NAME_AI) $(NAME_GUI)

re: fclean all

debug:
	$(MAKE) -C server debug
	$(MAKE) -C ai debug
	$(MAKE) -C gui debug

.PHONY: all server ai gui clean fclean re debug
