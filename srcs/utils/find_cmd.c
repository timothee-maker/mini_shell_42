/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:13:35 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/30 13:13:33 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    (void) exec;

    if (access(name, X_OK) == 0)
    {
		return (ft_strdup(name));
    }
    return (NULL);
}

int	fill_cmd(t_list *list, t_exec *exec, t_cmd *cmd)
{
	int	status;

	status = 0;
	while (list)
	{
		replace_env(list, exec);
		cmd = assign_cmd(list, exec);
		if (cmd == NULL)
		{
			status = 1;
		}
		add_command(exec, cmd);
		list = list->next_list;
	}
	if (exec->exit_status == 1)
		return (2);
	return (status);
}
