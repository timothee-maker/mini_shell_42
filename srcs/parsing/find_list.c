/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:19:39 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/14 17:41:04 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_builtin(char *new_str, t_list *list, int index)
{
	if (list->cmd == 1)
		return (0);
	if (ft_strcmp(new_str, "export") == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "BUILTIN",
				index));
	else if (ft_strcmp(new_str, "cd") == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "BUILTIN",
				index));
	else if (ft_strcmp(new_str, "unset") == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "BUILTIN",
				index));
	else if (ft_strcmp(new_str, "exit") == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "BUILTIN",
				index));
	else if (ft_strcmp(new_str, "env") == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "BUILTIN",
				index));
	else if (ft_strcmp(new_str, "pwd") == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "BUILTIN",
				index));
	else if (ft_strcmp(new_str, "echo") == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "BUILTIN",
				index));
	else
		return (0);
}

int	find_cmd(char *split, t_list *list, int index, char *new_str)
{
	char	**path;
	int		is_good;

	if (ft_strlen(new_str) == 0)
		return (empty_string_case(split, list, index), 0);
	if (access(new_str, X_OK) == 0 && list->cmd == 0)
		return (list->cmd = 1, add_token(list, ft_strdup(new_str), "CMD",
				index));
	path = ft_split(getenv("PATH"), ':');
	is_good = join_path(path, list, new_str, index);
	if (is_good == -1 || is_good == 1)
		return (is_good);
	if (new_str[0] == '$' && check_valid_dollar(split))
		is_good = add_token(list, remove_quotes_around(split), "ENV", index);
	else
		is_good = add_token(list, remove_quotes_around(split), "ARG", index);
	if (is_good == 1)
		is_good = 0;
	return (free_split(path), is_good);
}

int	join_path(char **path, t_list *list, char *new_str, int index)
{
	char	*tmp_cmd;
	char	*tmp_path;
	int		i;
	int		is_good;

	i = 0;
	while (path[i] && list->cmd == 0)
	{
		tmp_path = ft_strjoin(path[i++], "/");
		tmp_cmd = ft_strjoin(tmp_path, new_str);
		free(tmp_path);
		if (access(tmp_cmd, X_OK) == 0)
		{
			is_good = add_token(list, ft_strdup(tmp_cmd), "CMD", index);
			return (free_split(path), free(tmp_cmd), list->cmd = 1, is_good);
		}
		free(tmp_cmd);
	}
	return (0);
}

int	find_files_redir(char *split, t_list *list, int index, char *new_str)
{
	static int	redir = 0;

	if (ft_strncmp(">>", split, 2) == 0)
		return (redir = OUT_APPEND, 1);
	else if (ft_strncmp("<<", split, 2) == 0)
		return (redir = HERE_DOC, find_file(new_str, list, index, redir), 1);
	else if (ft_strchr(split, '<') && ft_strlen(split) == 1)
		return (redir = IN, 1);
	else if (ft_strchr(split, '>') && ft_strlen(split) == 1)
		return (redir = OUT, 1);
	else if (access(new_str, F_OK) == 0 && access(new_str, X_OK) != 0)
		return (find_file(new_str, list, index, redir), redir = NORMAL, 1);
	else if (redir == HERE_DOC)
		return (add_token(list, ft_strdup(new_str), "DELIMITER", index),
			redir = NORMAL, 1);
	else if (redir == OUT_APPEND)
		return (add_token(list, ft_strdup(new_str), "OUTFILE-APPEND", index),
			redir = NORMAL, 1);
	else if (redir == OUT)
		return (add_token(list, ft_strdup(new_str), "OUTFILE", index),
			redir = NORMAL, 1);
	else
		return (redir = NORMAL, 0);
}

void	find_file(char *split, t_list *list, int index, int redir)
{
	if (redir == IN)
		add_token(list, ft_strdup(split), "INFILE", index);
	else if (redir == OUT)
		add_token(list, ft_strdup(split), "OUTFILE", index);
	else if (redir == OUT_APPEND)
		add_token(list, ft_strdup(split), "OUTFILE-APPEND", index);
	else if (redir == HERE_DOC)
		add_token(list, ft_strdup(split), "HERE-DOC", index);
	else
		add_token(list, ft_strdup(split), "ARG", index);
}
