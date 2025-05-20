/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:05:15 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/20 15:05:16 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_next(t_cmd *cmd, t_exec *exec)
{
	char	*name;
	char	*value;
	t_env	*var;

	name = get_var_name(cmd->args[1]);
	value = get_var_value(cmd->args[1]);
	if (name == NULL || value == NULL)
	{
		if (name)
			free(name);
		if (value)
			free(value);
		return (0);
	}
	if (valid_identifier(name) == 0)
	{
		printf("export: \'%s\': not a valid identifier\n", cmd->args[1]);
		return (2);
	}
	var = get_var(exec, name);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	free(name);
	free(value);
	return (0);
}
