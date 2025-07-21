NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
CLIBS = -lreadline
SRC =	srcs/main.c \
		srcs/parsing/core.c srcs/parsing/find_list.c srcs/parsing/lst_utils.c srcs/parsing/parse.c srcs/parsing/utils.c srcs/parsing/utils2.c srcs/parsing/ft_split_minishell.c srcs/parsing/utils3.c srcs/parsing/utils_split.c srcs/parsing/clean_line.c \
		srcs/exec/checkers.c srcs/exec/exec_cmd.c srcs/exec/fork.c srcs/exec/heredoc.c srcs/exec/exec_cmd_2.c srcs/parsing/utils_split2.c\
		srcs/utils/args_utils.c srcs/utils/args.c srcs/utils/env.c srcs/utils/env2.c srcs/utils/files.c srcs/utils/find_cmd.c srcs/utils/ft_custom_join.c srcs/utils/ft_free.c srcs/utils/ft_malloc.c srcs/utils/init.c srcs/utils/init2.c srcs/utils/lst_utils.c srcs/utils/signal.c srcs/utils/signal_children.c srcs/utils/signal2.c \
		srcs/builtins/ft_cd_cases.c srcs/builtins/ft_cd.c srcs/builtins/ft_echo.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c srcs/builtins/ft_export.c srcs/builtins/ft_export_cases.c srcs/builtins/ft_pwd.c srcs/builtins/ft_unset.c

OBJS = $(SRC:.c=.o)

DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
BLUE = \033[0;94m
CYAN = \033[0;96m

.c.o:
	@cc $(CFLAGS) -c $< -o $@ -I includes

all: $(NAME)

libft/libft.a:
	@make -C libft

$(NAME): $(OBJS) libft/libft.a
	@cc $(OBJS) libft/libft.a -g -o $(NAME) $(CLIBS)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

clean:
	@rm -f $(OBJS) .infile .heredoc libft/*.o
	@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME) libft/libft.a
	@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re