/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:29 by lde-guil          #+#    #+#             */
/*   Updated: 2025/07/03 02:25:31 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_currpwd(t_exec *exec)
{
	t_env	*var;
	t_env	*prev;
	t_env	*temp;

	var = exec->env;
	prev = NULL;
	while (var)
	{
		if (!ft_strcmp(var->name, "PWD"))
		{
			free(var->value);
			return (var->value = getcwd(NULL, PATH_MAX), 0);
		}
		prev = var;
		var = var->next;
	}
	temp = ft_malloc(sizeof(t_env), 1, NULL);
	temp->name = ft_strdup("PWD");
	temp->value = ft_strdup(getcwd(NULL, PATH_MAX));
	temp->exported = 0;
	if (!temp->name || !temp->value)
		global_exit(exec, 0);
	return (temp->next = NULL, prev->next = temp, 1);
}

int	update_oldpwd(t_exec *exec, char path[PATH_MAX])
{
	t_env	*var;

	var = exec->env;
	while (var)
	{
		if (!ft_strcmp(var->name, "OLDPWD"))
		{
			free(var->value);
			var->value = ft_strdup(path);
			if (!var->value)
				global_exit(exec, 0);
			return (0);
		}
		var = var->next;
	}
	return (1);
}

int	update_pwds(t_exec *exec, char cwd[PATH_MAX])
{
	if (update_oldpwd(exec, cwd) == 1)
	{
		ft_putendl_fd("cd: Couldn't update OLDPWD", 2);
		return (1);
	}
	if (update_currpwd(exec) == 1)
	{
		ft_putendl_fd("cd: Couldn't update PWD", 2);
		return (1);
	}
	return (0);
}

int	home_case(t_exec *exec, char cwd[PATH_MAX])
{
	t_env	*var;

	var = exec->env;
	while (var)
	{
		if (!ft_strcmp(var->name, "HOME"))
		{
			if (chdir(var->value) == -1)
			{
				ft_putendl_fd("cd: No such file or directory", 2);
				return (1);
			}
			return (update_pwds(exec, cwd));
		}
		var = var->next;
	}
	ft_putendl_fd("cd: HOME not set", 2);
	return (1);
}

int	cd_change_dir(t_exec *exec, char cwd[PATH_MAX], char *path,
		int has_cwd)
{
	if (chdir(path) == -1)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		return (exec->exit_status = 1, 1);
	}
	if (has_cwd)
		return (exec->exit_status = 0, update_pwds(exec, cwd));
	else
		return (exec->exit_status = 0, 0);
}
