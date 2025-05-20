/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:07:30 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/20 15:07:38 by lde-guil         ###   ########.fr       */
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
	ft_putendl_fd("unset: did not found var", 2);
	return (2);
}

int	ft_unset(t_exec *exec, t_cmd *cmd)
{
	t_env	*var;
	char	*var_name;

	var = exec->env;
	if (cmd->args[1] == NULL)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return (2);
	}
	var_name = cmd->args[1];
	return (unset_loop(var, var_name));
}
