/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:12:24 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/18 17:31:02 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd_path(t_cmd *cmd, t_exec *exec)
{
	struct stat	st;

	if (!cmd->path || access(cmd->path, F_OK) != 0)
	{
		ft_putstr_fd(cmd->name, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exec->exit_status = 127;
		return (0);
	}
	if (stat(cmd->path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(cmd->name, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		exec->exit_status = 126;
		return (0);
	}
	if (access(cmd->path, X_OK) != 0)
	{
		ft_putstr_fd(cmd->name, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exec->exit_status = 126;
		return (0);
	}
	return (1);
}

int	exec_cmd(t_exec *exec, t_cmd *cmd)
{
	int	status;

    status = 1;
	if (cmd->is_builtin)
	{
		status = exec_builtin(exec, cmd);
		return (free_exec(exec), status);
	}
	if (check_cmd_path(cmd, exec))
	{
		if (execve(cmd->path, cmd->args, str_env(exec)) == -1)
		{
			perror(cmd->name);
			exec->exit_status = 1;
			return (free_exec(exec), status);
		}
	}
	return (free_exec(exec), status);
}
