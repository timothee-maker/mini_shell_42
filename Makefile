NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
CLIBS = -lreadline
SRC =	srcs/main.c \
		srcs/parsing/core.c srcs/parsing/find_list.c srcs/parsing/lst_utils.c srcs/parsing/parse.c srcs/parsing/utils.c srcs/parsing/ft_split_minishell.c \
		srcs/exec/exec_cmd.c srcs/exec/fork.c srcs/exec/heredoc.c srcs/exec/output.c \
		srcs/utils/args.c srcs/utils/env.c srcs/utils/files.c srcs/utils/files2.c srcs/utils/find_cmd.c srcs/utils/ft_free.c srcs/utils/init.c \

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
	@rm -f $(OBJS) .infile .outfile .stdin
	@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME) libft/libft.a
	@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re: fclean
	@make all

.PHONY: all clean fclean re
