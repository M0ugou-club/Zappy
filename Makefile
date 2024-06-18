##
## EPITECH PROJECT, 2024
## Zappy [WSL: Fedora]
## File description:
## Makefile
##

NAME_SERVER = zappy_server
NAME_AI = zappy_ai
NAME_GUI = zappy_gui

SERVER_PATH = server
GUI_PATH = client/gui
AI_PATH = client/ai

COLOR_GREEN = \033[0;32m
COLOR_BLUE = \033[0;34m
COLOR_YELLOW = \033[0;33m
COLOR_RESET = \033[0m

all: server gui ai

server:
	@$(MAKE) -C $(SERVER_PATH)
	@cp $(SERVER_PATH)/$(NAME_SERVER) .
	@echo -e "$(COLOR_GREEN)[OK] $(COLOR_YELLOW)$(NAME_SERVER) $(COLOR_BLUE)\
		moved to root directory$(COLOR_RESET)"

ai:
	@$(MAKE) -C $(AI_PATH)
	@cp $(AI_PATH)/$(NAME_AI) .
	@echo -e "$(COLOR_GREEN)[OK] $(COLOR_YELLOW)$(NAME_AI) $(COLOR_BLUE)\
		moved to root directory$(COLOR_RESET)"

gui:
	@$(MAKE) -C $(GUI_PATH)
	@cp $(GUI_PATH)/$(NAME_GUI) .
	@echo -e "$(COLOR_GREEN)[OK] $(COLOR_YELLOW)$(NAME_GUI) $(COLOR_BLUE)\
		moved to root directory$(COLOR_RESET)"


clean:
	@$(MAKE) -C $(SERVER_PATH) clean
	@$(MAKE) -C $(GUI_PATH) clean
	@$(MAKE) -C $(AI_PATH) clean

fclean: clean
	@rm -f $(NAME_SERVER) $(NAME_AI) $(NAME_GUI)

re: fclean all

debug:
	@$(MAKE) -C $(SERVER_PATH) debug
	@$(MAKE) -C $(GUI_PATH) debug
	@$(MAKE) -C $(AI_PATH) debug

.PHONY: all server ai gui clean fclean re debug
