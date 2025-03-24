NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
CLIBS = -lreadline
SRC =	main.c \
		exec/create_env.c exec/utils.c exec/find_cmd.c exec/exec.c exec/init.c exec/ft_free.c \
		builtins/ft_cd.c builtins/ft_echo.c builtins/ft_pwd.c \
		parsing/core.c parsing/find_list.c parsing/lst_utils.c parsing/parse.c parsing/utils.c \

OBJS = $(SRC:.c=.o)

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.c.o:
	@cc $(CFLAGS) -c $< -o $@

all: $(NAME)

lib:
	@make -C libft
	@make clean -C libft

$(NAME): lib $(OBJS)
	@cc $(OBJS) libft/libft.a -o $(NAME) $(CLIBS)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

clean: 
	@rm -f $(OBJS)
	@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME) libft/libft.a
	@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re: fclean
	@make all

.PHONY: all clean fclean re