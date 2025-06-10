/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:05:15 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/10 16:01:20 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	put_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

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
	res = malloc(sizeof(t_env));
	res->name = NULL;
	res->value = NULL;
	res->next = NULL;
	res->exported = 1;
	var->next = res;
	return (res);
}

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
		put_error("export: ", cmd->args[1], ": not a valid identifier\n");
		return (1);
	}
	var = get_var(exec, name);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	free(name);
	free(value);
	return (0);
}
