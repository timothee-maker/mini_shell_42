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

typedef struct s_element
{
	char				*arg;
	char				*token;
	int					position;
	struct s_element	*next;
}	t_element;

typedef struct s_list
{
	t_element	*first;
} 	t_list;

void 	free_split(char **split);
void 	minishell(char *line, char **env, t_list *list);
t_list	*initialisation(void);
void	afficherliste(t_list *liste);
void	insertion_f(t_list *liste, char *arg, char *token, int index);
void	destruction(t_list *liste);

#endif