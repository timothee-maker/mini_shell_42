/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:24:33 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/30 13:38:40 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_exec *exec, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		has_cwd;

	has_cwd = 1;
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putendl_fd("cd: Cannot access current directory", 2);
		has_cwd = 0;
	}
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (exec->exit_status = 1, 1);
	}
	else if (cmd->args[1] != NULL)
		return (cd_change_dir(exec, cwd, cmd->args[1], has_cwd));
	else
	{
		if (has_cwd)
			return (exec->exit_status = 0, home_case(exec, cwd));
		else
			return (exec->exit_status = 0, 0);
	}
}
