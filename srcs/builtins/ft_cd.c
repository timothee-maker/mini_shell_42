/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:24:33 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/20 09:24:35 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_currpwd(t_env *var, char *path)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putendl_fd("cd: Cannot access current directory", 2);
		return (1);
	}
	while (var)
	{
		if (!ft_strncmp(var->name, "PWD", ft_strlen(var->name) + 6))
		{
			free(var->value);
			var->value = ft_strdup(path);
			return (0);
		}
		var = var->next;
	}
	return (1);
}

int	update_oldpwd(t_env *var)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putendl_fd("cd: Cannot access current directory", 2);
		return (1);
	}
	while (var)
	{
		if (!ft_strncmp(var->name, "OLDPWD", ft_strlen(var->name) + 6))
		{
			free(var->value);
			var->value = ft_strdup(cwd);
			return (0);
		}
		var = var->next;
	}
	return (1);
}

int	ft_cd(t_exec *exec, t_cmd *cmd)
{
	int		res;
	t_env	*var;

	var = exec->env;
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (2);
	}
	if (!cmd->args[1])
	{
		return (home_case(exec, var));
	}
	else if (!ft_strncmp(cmd->args[1], "-", ft_strlen(cmd->args[1]) + 1))
		return (reverse_case(exec, var));
	else
		res = base_case(var, cmd->args);
	if (res < 0)
		res *= -1;
	return (res);
}
