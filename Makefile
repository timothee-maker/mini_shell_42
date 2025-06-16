NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
CLIBS = -lreadline
SRC =	srcs/main.c \
		srcs/parsing/core.c srcs/parsing/find_list.c srcs/parsing/lst_utils.c srcs/parsing/parse.c srcs/parsing/utils.c srcs/parsing/utils2.c srcs/parsing/ft_split_minishell.c srcs/parsing/utils3.c srcs/parsing/utils_split.c \
		srcs/parsing/find_list2.c srcs/parsing/clean_line.c\
		srcs/exec/checkers.c srcs/exec/exec_cmd.c srcs/exec/fork.c srcs/exec/heredoc.c srcs/exec/exec_cmd_2.c \
		srcs/utils/args_utils.c srcs/utils/args.c srcs/utils/env.c srcs/utils/env2.c srcs/utils/files.c srcs/utils/find_cmd.c srcs/utils/ft_custom_join.c srcs/utils/ft_free.c srcs/utils/init.c srcs/utils/init2.c srcs/utils/lst_utils.c srcs/utils/signal.c srcs/utils/signal_children.c\
		srcs/utils/signal2.c\
		srcs/builtins/ft_cd_cases.c srcs/builtins/ft_cd.c srcs/builtins/ft_echo.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c srcs/builtins/ft_export.c srcs/builtins/ft_export_cases.c srcs/builtins/ft_pwd.c srcs/builtins/ft_unset.c \

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
	@cc $(CFLAGS) -c $< -o $@ -I includes

all: $(NAME)

lib:
	@make -C libft
	@make clean -C libft

$(NAME): lib $(OBJS)
	@cc $(OBJS) libft/libft.a -g -o $(NAME) $(CLIBS)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

clean: 
	@rm -f $(OBJS) .infile .heredoc
	@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME) libft/libft.a
	@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

fast: re
	@make clean
	@clear

re: fclean
	@make all

.PHONY: all clean fclean re
