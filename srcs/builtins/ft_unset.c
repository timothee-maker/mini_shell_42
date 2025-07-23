/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:07:30 by lde-guil          #+#    #+#             */
/*   Updated: 2025/07/23 14:51:02 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_loop(t_env *var, char *varname, t_exec *exec)
{
	t_env	*prev;

	prev = NULL;
	while (var)
	{
		if (!ft_strcmp(var->name, varname))
		{
			if (var->name)
				free(var->name);
			if (var->value)
				free(var->value);
			if (prev == NULL)
				exec->env = var->next;
			if (prev != NULL)
				prev->next = var->next;
			free(var);
			return (0);
		}
		prev = var;
		var = var->next;
	}
	return (0);
}

int	ft_unset(t_exec *exec, t_cmd *cmd)
{
	t_env	*var;
	char	*var_name;
	int		i;
	int		status;

	i = 1;
	if (cmd->args[1] == NULL)
		return (exec->exit_status = 0, 0);
	while (cmd->args[i])
	{
		var = exec->env;
		var_name = cmd->args[i];
		exec->exit_status = 0;
		status = unset_loop(var, var_name, exec);
		i++;
	}
	return (status);
}
