#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <fcntl.h>

# define DELIMITER "|<>"
#	define QUOTES "\'\""

typedef struct s_element
{
	char				*arg;
	char				*token;
	int					position;
	struct s_element	*next;
}	t_element;

typedef struct s_list
{
	t_element		*first;
	struct	s_list	*next_list;
} 	t_list;

void 	free_split(char **split);
void 	minishell(char *line, t_list *list);
t_list	*initialisation(void);
void	afficherliste(t_list *liste);
void	insertion_element(t_list *liste, char *arg, char *token, int index);
void	insertion_list(t_list *liste);
void	destruction(t_list *liste);
char	*clean_line(char *line);

int		find_builtin(char *split, t_list *list, int index);
int		find_cmd(char *split, t_list *list, int index);
void	find_opt_arg(char *split, t_list *list, int index);
int		find_token(char *split, t_list *list, int index);
void	find_file(char *split, t_list *list, int index, int redir);

int		len_tab(char **split);


#endif