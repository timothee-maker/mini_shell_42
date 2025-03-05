/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:53:56 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/05 10:29:45 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NORMAL 0
#define IN 1
#define OUT 2
#define OUT_APPEND 3

void	analyze_line(char **split, t_list *list);
void	execute_line(char **split, char **env);
void	minishell(char	*line, char **env, t_list *list);
int		find_token(char *split, t_list *list, int index);
void	find_file(char *split, t_list *list, int index, int redir);
void	find_cmd(char *split, t_list *list, int index);

int main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*list;

	list = initialisation();
	while (1)
	{
		input = readline("shell_de_l'empereur : ");
		if (input)
		{
			minishell(input, env, list);
			add_history(input);
			afficherliste(list);
			destruction(list);
		}
		else
			exit(1);
		free(input);
	}
}

void	minishell(char	*line, char **env, t_list *list)
{
	char	**split;
	int		nb_pipe;

	split = ft_split(line, ' ');
	analyze_line(split, list);

	// if (split[0])
	// 	execute_line(split, env);	
	free_split(split);
}

void	analyze_line(char **split, t_list *list)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (!find_token(split[i], list, i))
			find_cmd(split[i], list, i);
		i++;
	}
}

void	find_cmd(char *split, t_list *list, int index)
{
	static int	arg = 0;
	char		**path;
	char		*tmp_cmd;
	int			i;

	if (access(split, X_OK) == 0)
	{
		insertion_f(list, ft_strdup(split), "CMD", index);
		arg = 1;
		return ;
	}
	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		tmp_cmd = ft_strjoin(path[i++], split);
		if (access(tmp_cmd, X_OK) == 0)
		{
			insertion_f(list, ft_strdup(split), "CMD", index);
			arg = 1;
			free(tmp_cmd);
			return ;
		}
		free(tmp_cmd);
	}
	free_split(path);
	if (arg == 1)
			insertion_f(list, ft_strdup(split), "ARG", index);
	arg = 0;
}

int	find_token(char *split, t_list *list, int index)
{
	static int	redir = 0;

	if (ft_strchr(split, '<') && ft_strlen(split) == 1)
	{
		insertion_f(list, ft_strdup("<"), "REDIR-IN", index);
		redir = IN;
	}
	else if (ft_strchr(split, '|') && ft_strlen(split) == 1)
		insertion_f(list, ft_strdup("|"), "pipe", index);
	else if (ft_strchr(split, '>') && ft_strlen(split) == 1)
	{
		insertion_f(list, ft_strdup(">"), "REDIR-OUT", index);
		redir = OUT;
	}
	else if (ft_strncmp(">>", split, 2) == 0)
	{
		insertion_f(list, ft_strdup(">>"), "REDIR-OUT_APPEND", index);
		redir = OUT_APPEND;
	}
	else if (access(split, F_OK) == 0 && access(split, X_OK) != 0)
	{
		find_file(split, list, index, redir);
		redir = NORMAL;
	}
	else
	{
		redir = NORMAL;
		return (0);
	}
	return (1);
}

void	find_file(char *split, t_list *list, int index, int redir)
{
	if (redir == IN)
		insertion_f(list, ft_strdup(split), "FILE-IN", index);
	else if (redir == OUT)
		insertion_f(list, ft_strdup(split), "FILE-OUT", index);
	else if (redir == OUT_APPEND)
		insertion_f(list, ft_strdup(split), "FILE-OUT-APPEND", index);
	else
		insertion_f(list, ft_strdup(split), "FILE", index);
}

void	execute_line(char **split, char **env)
{
		if (execve(split[0], split, env) == -1)
		{
			perror("Error execve");
			free_split(split);
			exit(1);
		}
}
