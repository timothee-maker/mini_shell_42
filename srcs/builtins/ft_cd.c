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

static int	update_currpwd(t_exec *exec, char *path)
{
	t_env	*var;

	var = exec->env;
	while (var)
	{
		if (!ft_strcmp(var->name, "PWD"))
		{
			free(var->value);
			var->value = ft_strdup(path);
			return (0);
		}
		var = var->next;
	}
	return (1);
}

static int	update_oldpwd(t_exec *exec, char path[PATH_MAX])
{
	t_env *var;

    var = exec->env;
	while (var)
	{
		if (!ft_strcmp(var->name, "OLDPWD"))
		{
			free(var->value);
			var->value = ft_strdup(path);
			return (0);
		}
		var = var->next;
	}
	return (1);
}

static int update_pwds(t_exec *exec, char cwd[PATH_MAX], char *destination)
{
    if (update_oldpwd(exec, cwd) == 1)
    {
        ft_putendl_fd("cd: Couldn't update OLDPWD", 2);
        return (1);
    }
    if (update_currpwd(exec, destination) == 1)
    {
        ft_putendl_fd("cd: Couldn't update PWD", 2);
        return (1);
    }
    return (0);
}

static int home_case(t_exec *exec, char cwd[PATH_MAX])
{
    t_env *var;

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
            return (update_pwds(exec, cwd, var->value));
        }
        var = var->next;
    }
    ft_putendl_fd("cd: HOME not set", 2);
    return (1);
}

int	ft_cd(t_exec *exec, t_cmd *cmd)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        ft_putendl_fd("cd: Cannot access current directory", 2);
        return (1);
    }
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (2);
	}
    else if (cmd->args[1] != NULL)
    {
        if (chdir(cmd->args[1]) == -1)
        {
            ft_putendl_fd("cd: No such file or directory", 2);
            return (1);
        }
        return (update_pwds(exec, cwd, cmd->args[1]));
    }
    else
        return home_case(exec, cwd);
}
