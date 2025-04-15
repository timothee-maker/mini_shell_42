/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:19:39 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/15 11:51:52 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_builtin(char *split, t_list *list, int index)
{
	char	*new_str;

	new_str = remove_quotes(split);
	if (strcmp(new_str, "export") == 0)
		return (add_token(list, ft_strdup(split), "BUILTIN", index),
			free(new_str), 1);
	else if (strcmp(new_str, "cd") == 0)
		return (add_token(list, ft_strdup(split), "BUILTIN", index),
			free(new_str), 1);
	else if (strcmp(new_str, "unset") == 0)
		return (add_token(list, ft_strdup(split), "BUILTIN", index),
			free(new_str), 1);
	else if (strcmp(new_str, "exit") == 0)
		return (add_token(list, ft_strdup(split), "BUILTIN", index),
			free(new_str), 1);
    else if (strcmp(new_str, "env") == 0)
        return (add_token(list, ft_strdup(split), "BUILTIN", index),
            free(new_str), 1);
    else if (strcmp(new_str, "pwd") == 0)
        return (add_token(list, ft_strdup(split), "BUILTIN", index),
            free(new_str), 1);
    else if (strcmp(new_str, "echo") == 0)
        return (add_token(list, ft_strdup(split), "BUILTIN", index),
			free(new_str), 1);
	else
		return (free(new_str), 0);
}

int	find_cmd(char *split, t_list *list, int index)
{
	char		**path;
	char		*tmp_cmd;
	char        *tmp_path;
	char		*new_str;
	int			i;

	new_str = remove_quotes(split);
	if (ft_strlen(new_str) == 0)
		return (free(new_str), 0);
	if (access(new_str, X_OK) == 0 && list->cmd == 0)
		return (add_token(list, ft_strdup(split), "CMD", index), list->cmd = 1, 1);
	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i] && list->cmd == 0)
	{
		tmp_path = ft_strjoin(path[i++], "/");
		tmp_cmd = ft_strjoin(tmp_path, new_str);
		free(tmp_path);
		if (access(tmp_cmd, X_OK) == 0)
			return (add_token(list, ft_strdup(tmp_cmd), "CMD", index),
				free_split(path), free(tmp_cmd), free(new_str), list->cmd = 1, 1);
		free(tmp_cmd);
	}
	add_token(list, ft_strdup(split), "ARG", index);
	return (free_split(path), free(new_str), 0);
}

void	find_opt_arg(char *split, t_list *list, int index)
{
	if (split[0] == '\"')
		add_token(list, ft_strdup(split), "DOUBLE-QUOTE", index);
	else if (split[0] == '\'')
		add_token(list, ft_strdup(split), "SIMPLE-QUOTE", index);
	else
		add_token(list, ft_strdup(split), "ARG", index);
}

int	find_files_redir(char *split, t_list *list, int index)
{
	static int	redir = 0;

	if (ft_strncmp(">>", split, 2) == 0)
		return (redir = OUT_APPEND, 1);
	else if (ft_strncmp("<<", split, 2) == 0)
		return (redir = HERE_DOC, 1);
	else if (ft_strchr(split, '<') && ft_strlen(split) == 1)
		return (redir = IN, 1);
	else if (ft_strchr(split, '>') && ft_strlen(split) == 1)
		return (redir = OUT, 1);
	else if (access(split, F_OK) == 0 && access(split, X_OK) != 0)
		return(find_file(split, list, index, redir), redir = NORMAL, 0);
	else if (redir == HERE_DOC)
		return (add_token(list, ft_strdup(split), "DELIMITER", index), redir = NORMAL, 1);
	else if (redir == OUT_APPEND)
		return (add_token(list, ft_strdup(split), "OUTFILE-APPEND", index), redir = NORMAL, 1);
	else if (redir == OUT)
		return (add_token(list, ft_strdup(split), "OUTFILE", index), redir = NORMAL, 1);
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
	else
		add_token(list, ft_strdup(split), "FILE", index);
}
