/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:07:30 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/10 16:00:06 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_loop(t_env *var, char *varname)
{
	t_env	*prev;

	prev = NULL;
	while (var)
	{
		if (!ft_strcmp(var->name, varname))
		{
			free(var->name);
			if (var->value)
				free(var->value);
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

	var = exec->env;
	if (cmd->args[1] == NULL)
		return (exec->exit_status = 0, 0);
	var_name = cmd->args[1];
	return (exec->exit_status = 0, unset_loop(var, var_name));
}
