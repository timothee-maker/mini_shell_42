/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:12:24 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/16 11:23:26 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd_error(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (127);
	if (S_ISDIR(sb.st_mode))
		return (126);
	if (access(path, X_OK) != 0)
		return (126);
	return (0);
}

static int	handle_cmd_error(t_exec *exec, t_cmd *cmd)
{
	int	check;

	check = check_cmd_error(cmd->path);
	if (check == 126)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd->path, 2),
			ft_putstr_fd(": Permission denied\n", 2), free_exec(exec), 126);
	else if (check == 127)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd->path, 2),
			ft_putstr_fd(": No such file\n", 2), free_exec(exec), 127);
    else if (cmd->path == NULL)
	{
		ft_putstr_fd("Command not found", 2);
		if (cmd->name)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->name, 2);
		}
		return (ft_putstr_fd("\n", 2), free_exec(exec), 127);
	}
	return (0);
}

int	exec_cmd(t_exec *exec, t_cmd *cmd)
{
	int	status;
	int	check;

	if (cmd->is_builtin)
	{
		status = exec_builtin(exec, cmd);
		return (free_exec(exec), status);
	}
	check = handle_cmd_error(exec, cmd);
	if (check != 0)
		return (check);
	if (execve(cmd->path, cmd->args, str_env(exec)) == -1)
	{
		exec->exit_status = 1;
		perror("Execve error");
		return (free_exec(exec), 2);
	}
	return (0);
}
