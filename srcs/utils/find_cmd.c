/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:13:35 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/27 14:23:49 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_loop(char *path, char **path_tab, char *name, int i)
{
	char	*temp;

	temp = NULL;
	if (access(name, X_OK) == 0)
	{
		return (ft_strdup(name));
	}
	if (path_tab[i])
	{
		temp = ft_strjoin(path_tab[i], "/");
		temp = ft_custom_join(temp, name);
	}
	if (temp)
	{
		if (access(temp, X_OK) == 0)
		{
			free(path);
			free_tab(path_tab);
			return (temp);
		}
		free(temp);
	}
	return (NULL);
}

char	*get_cmd_name(char *path)
{
	int		i;
	char	*res;
	char	**chunks;

	chunks = ft_split(path, '/');
	res = NULL;
	i = 0;
	while (chunks[i])
	{
		if (!chunks[i + 1])
			res = ft_strdup(chunks[i]);
		i++;
	}
	free_tab(chunks);
	return (res);
}

char	*find_path(char *name, t_exec *exec)
{
	char	*path;
	char	*temp;
	char	**path_tab;
	int		i;

	path = fetch_value("$PATH", exec);
	if (path == NULL)
		path = BACKUP_PATH;
	path_tab = ft_split(path, ':');
	i = 0;
	while (path_tab[i++])
	{
		temp = path_loop(path, path_tab, name, i);
		if (temp)
			return (temp);
	}
	free_tab(path_tab);
	free(path);
	return (NULL);
}
