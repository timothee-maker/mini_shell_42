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

static int	exit_execve_errno(void)
{
	if (errno == EACCES)
		return(126);
	else if (errno == ENOEXEC)
		return(126);
	else if (errno == ENOENT)
		return(127);
	else
		return(1);
}

static int	handle_cmd_error(t_exec *exec, t_cmd *cmd)
{
    struct stat statbuf;

    if (!cmd->name || !*cmd->name)
        return (ft_putstr_fd("Command not found\n", STDERR_FILENO), 127);

    if (cmd->path == NULL)
    {
        if (stat(cmd->name, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
                return (ft_putstr_fd("Is a directory\n", STDERR_FILENO), 126);
            if (access(cmd->name, X_OK) != 0)
                return (ft_putstr_fd("Permission denied\n", STDERR_FILENO), 126);
        }
        else
            return (ft_putstr_fd("Command not found\n", STDERR_FILENO), 127);
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
		return (free_exec(exec), exit_execve_errno());
	}
	return (0);
}
