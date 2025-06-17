/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:12:24 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/17 15:36:17 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execve_handler(t_cmd *cmd)
{
    struct stat statbuf;

    if (!cmd->path || access(cmd->path, F_OK) != 0)
    {
        ft_putstr_fd(cmd->name, STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
    }
    if (stat(cmd->path, &statbuf) == 0)
    {
        if (S_ISDIR(statbuf.st_mode))
        {
            ft_putstr_fd(cmd->name, STDERR_FILENO);
            ft_putstr_fd(": is a directory\n", STDERR_FILENO);
            return (126);
        }
        if (access(cmd->path, X_OK) != 0)
        {
            ft_putstr_fd(cmd->name, STDERR_FILENO);
            ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
            return (126);
        }
    }
    return (126);
}

int	exec_cmd(t_exec *exec, t_cmd *cmd)
{
	int	status;

	if (cmd->is_builtin)
	{
		status = exec_builtin(exec, cmd);
		return (free_exec(exec), status);
	}
	if (execve(cmd->path, cmd->args, str_env(exec)) == -1)
	{
		exec->exit_status = 1;
		return (free_exec(exec), execve_handler(cmd));
	}
	return (0);
}
