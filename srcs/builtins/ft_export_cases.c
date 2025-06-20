/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:05:15 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/19 11:19:45 by tnolent          ###   ########.fr       */
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

static int	handle_export_value_null(char *name, char *value, t_cmd *cmd,
		t_exec *exec)
{
	if (check_export_identifier(name, cmd->args[1], exec))
	{
		if (value)
			free(value);
		return (1);
	}
	if (name)
		free(name);
	if (value)
		free(value);
	return (0);
}

int	export_next(t_cmd *cmd, t_exec *exec)
{
	char	*name;
	char	*value;
	t_env	*var;

	name = get_var_name(cmd->args[1]);
	value = get_var_value(cmd->args[1]);
	if (value == NULL)
		return (handle_export_value_null(name, value, cmd, exec));
	if (check_export_identifier(name, cmd->args[1], exec))
		return (free(value), 1);
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
	return (0);
}
