/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:19:15 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/27 15:35:17 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_single_builtin(t_cmd *cmd)
{
	if (cmd->is_builtin == 0)
		return (0);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (0);
	return (1);
}

void	exec_single_builtin(t_cmd *cmd, t_exec *exec)
{
	int	stdout_backup;

	close(exec->pipe[0]);
	close(exec->pipe[1]);
	stdout_backup = -1;
	if (cmd->output >= 0)
	{
		stdout_backup = dup(1);
		if (dup2(cmd->output, STDOUT_FILENO) == -1)
		{
			perror("dup error");
			return ;
		}
		close(cmd->output);
	}
	exec->exit_status = exec_builtin(exec, cmd);
	if (cmd->output >= 0)
	{
		if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		{
			perror("dup error");
			return ;
		}
		close(stdout_backup);
	}
}
