/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:19:39 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/28 19:42:12 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_env(t_list *list, t_token *token, t_exec *exec);

int	find_builtin(t_list *list, t_token *token)
{
	if (list->cmd == 1)
		return (0);
	if (ft_strcmp(token->split->str, "export") == 0)
		return (list->cmd = 1, add_token(list, "BUILTIN", token));
	else if (ft_strcmp(token->split->str, "cd") == 0)
		return (list->cmd = 1, add_token(list, "BUILTIN", token));
	else if (ft_strcmp(token->split->str, "unset") == 0)
		return (list->cmd = 1, add_token(list, "BUILTIN", token));
	else if (ft_strcmp(token->split->str, "exit") == 0)
		return (list->cmd = 1, add_token(list, "BUILTIN", token));
	else if (ft_strcmp(token->split->str, "env") == 0)
		return (list->cmd = 1, add_token(list, "BUILTIN", token));
	else if (ft_strcmp(token->split->str, "pwd") == 0)
		return (list->cmd = 1, add_token(list, "BUILTIN", token));
	else if (ft_strcmp(token->split->str, "echo") == 0)
		return (list->cmd = 1, add_token(list, "BUILTIN", token));
	else
		return (0);
}

int	find_cmd(t_list *list, t_token *token)
{
	char	**path;
	int		is_good;

	is_good = 0;
	if (ft_strlen(token->split->str) == 0)
		return (empty_string_case(token->split->str, list, token), 0);
	if (access(token->split->str, X_OK) == 0 && list->cmd == 0)
		return (list->cmd = 1, add_token(list, "CMD", token));
	if (getenv("PATH"))
	{
		path = ft_split(getenv("PATH"), ':');
		is_good = join_path(path, list, token);
		if (is_good == -1 || is_good == 1)
			return (is_good);
		free_tab(path);
	}
	if (is_good == 1)
		is_good = 0;
	return (is_good);
}

int	handle_env(t_list *list, t_token *token, t_exec *exec)
{
	int		is_good;
	char	*tmp_env;

	is_good = 0;
	if (token->split->str[0] == '$' && token->split->env_context != 2)
	{
		tmp_env = token->split->str;
		token->split->str = fetch_value(token->split->str, exec);
		if (!tmp_env)
			return (-1);
		is_good = find_builtin(list, token);
		if (!is_good)
		{
			is_good = find_files_redir(list, token);
			if (!is_good)
				is_good = find_cmd(list, token);
		}
	}
	if (!is_good)
		is_good = add_token(list, "ARG", token);
	return (is_good);
}

int	find_files_redir(t_list *list, t_token *token)
{
	static int	redir;

	if (token->position == 0 || token->redir == 0)
		redir = 0;
	if (ft_strncmp(">>", token->split->str, 2) == 0)
		return (redir = OUT_APPEND, token->redir = 1, 1);
	else if (ft_strncmp("<<", token->split->str, 2) == 0)
		return (redir = 4, token->redir = 1, find_file(list, redir, token), 1);
	else if (token->split->str[0] == '<')
		return (redir = IN, token->redir = 1, 1);
	else if (token->split->str[0] == '>')
		return (redir = OUT, token->redir = 1, 1);
	else if (redir == IN || redir == OUT || redir == OUT_APPEND)
		return (find_file(list, redir, token), redir = 0, token->redir = 1, 1);
	else if (redir == HERE_DOC)
		return (add_token(list, "DELIMITER", token),
			redir = NORMAL, token->redir = 1, 1);
	else if (redir == OUT_APPEND)
		return (add_token(list, "OUTFILE-APPEND", token),
			redir = NORMAL, token->redir = 1, 1);
	else if (redir == OUT)
		return (add_token(list, "OUTFILE", token),
			redir = NORMAL, token->redir = 1, 1);
	else
		return (redir = NORMAL, 0);
}

void	find_file(t_list *list, int redir, t_token *token)
{
	if (redir == IN)
		add_token(list, "INFILE", token);
	else if (redir == OUT)
		add_token(list, "OUTFILE", token);
	else if (redir == OUT_APPEND)
		add_token(list, "OUTFILE-APPEND", token);
	else if (redir == HERE_DOC)
		add_token(list, "HERE-DOC", token);
	else
		add_token(list, "ARG", token);
}

int	join_path(char **path, t_list *list, t_token *token)
{
	char	*tmp_cmd;
	char	*tmp_path;
	int		i;
	int		is_good;

	i = 0;
	while (path[i] && list->cmd == 0)
	{
		tmp_path = ft_strjoin(path[i++], "/");
		tmp_cmd = ft_strjoin(tmp_path, token->split->str);
		free(tmp_path);
		if (access(tmp_cmd, X_OK) == 0)
		{
			free(token->split->str);
			token->split->str = ft_strdup(tmp_cmd);
			is_good = add_token(list, "CMD", token);
			return (free_tab(path), free(tmp_cmd), list->cmd = 1, is_good);
		}
		free(tmp_cmd);
	}
	return (0);
}
