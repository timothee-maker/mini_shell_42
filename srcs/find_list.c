/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:19:39 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/07 16:30:37 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NORMAL 0
#define IN 1
#define OUT 2
#define OUT_APPEND 3

int	find_builtin(char *split, t_list *list, int index)
{
	if (strcmp(split, "export") == 0)
		return (insertion_f(list, ft_strdup(split), "BUILTIN", index), 1);
	else if (strcmp(split, "env") == 0)
		return (insertion_f(list, ft_strdup(split), "BUILTIN", index), 1);
	else if (strcmp(split, "pwd") == 0)
		return (insertion_f(list, ft_strdup(split), "BUILTIN", index), 1);
	else if (strcmp(split, "cd") == 0)
		return (insertion_f(list, ft_strdup(split), "BUILTIN", index), 1);
	else if (strcmp(split, "unset") == 0)
		return (insertion_f(list, ft_strdup(split), "BUILTIN", index), 1);
	else if (strcmp(split, "exit") == 0)
		return (insertion_f(list, ft_strdup(split), "BUILTIN", index), 1);
	else if (strcmp(split, "echo") == 0)
		return (insertion_f(list, ft_strdup(split), "BUILTIN", index), 1);
	else
		return (0);
}

int	find_cmd(char *split, t_list *list, int index)
{
	static int	arg = 0;
	char		**path;
	char		*tmp_cmd;
	int			i;

	if (access(split, X_OK) == 0)
		return (insertion_f(list, ft_strdup(split), "CMD", index), 1);
	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		tmp_cmd = ft_strjoin(path[i++], split);
		if (access(tmp_cmd, X_OK) == 0)
			return (insertion_f(list, ft_strdup(split), "CMD", index),
				free_split(path), free(tmp_cmd), 1);
		free(tmp_cmd);
	}
	return (free_split(path), 0);
}

void	find_opt_arg(char *split, t_list *list, int index)
{
	if (split[0] == '-')
		insertion_f(list, ft_strdup(split), "OPT", index);
	else
		insertion_f(list, ft_strdup(split), "ARG", index);
}

int	find_token(char *split, t_list *list, int index)
{
	static int	redir = 0;

	if (ft_strncmp(">>", split, 2) == 0)
		return (insertion_f(list, ft_strdup(">>"), "REDIR-OUT_APPEND", index), redir = OUT_APPEND, 1);
	else if (ft_strchr(split, '<') && ft_strlen(split) == 1)
		return (insertion_f(list, ft_strdup("<"), "REDIR-IN", index), redir = IN, 1);
	else if (ft_strchr(split, '|') && ft_strlen(split) == 1)
		return (insertion_f(list, ft_strdup("|"), "pipe", index), 1);
	else if (ft_strchr(split, '>') && ft_strlen(split) == 1)
		return (insertion_f(list, ft_strdup(">"), "REDIR-OUT", index), redir = OUT, 1);
	else if (access(split, F_OK) == 0 && access(split, X_OK) != 0)
		return(find_file(split, list, index, redir), redir = NORMAL, 1);
	else
		return (redir = NORMAL, 0);
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
