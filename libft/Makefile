NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -g
SRC = ft_strcmp.c ft_split.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strncpy.c
INC = includes
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

.c.o:
	@cc $(CFLAGS) -c $< -o $@

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

.PHONY: clean fclean re all