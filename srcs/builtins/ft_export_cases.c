/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:05:15 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/27 09:53:15 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		if (ft_strchr("!@#$%%^&*()-", str[i]))
			return (0);
		i++;
	}
	return (1);
}

static t_env	*get_var(t_exec *exec, char *name)
{
	t_env	*var;
	t_env	*res;

	var = exec->env;
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			return (var);
		if (var->next != NULL)
			var = var->next;
		else
			break ;
	}
	res = ft_malloc(sizeof(t_env), 1, NULL);
	res->name = NULL;
	res->value = NULL;
	res->next = NULL;
	res->exported = 1;
	var->next = res;
	return (res);
}

static int	check_export_identifier(char *name, char *arg, t_exec *exec)
{
	if (!valid_identifier(name))
	{
		put_error("export: ", arg, ": not a valid identifier\n");
		exec->exit_status = 1;
		free(name);
		return (1);
	}
	return (0);
}

static void	export_loop(t_cmd *cmd, t_exec *exec, int i)
{
	char	*name;
	char	*value;
	t_env	*var;

	name = get_var_name(cmd->args[i]);
	value = get_var_value(cmd->args[i]);
	if (check_export_identifier(name, cmd->args[i], exec))
	{
		free(value);
		return ;
	}
	var = get_var(exec, name);
	if (var->name)
		free(var->name);
	var->name = ft_strdup(name);
	if (value != NULL)
	{
		if (var->value)
			free(var->value);
		var->value = ft_strdup(value);
	}
	free(name);
	if (value != NULL)
		free(value);
}

int	export_next(t_cmd *cmd, t_exec *exec)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		export_loop(cmd, exec, i);
		i++;
	}
	return (0);
}
