/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:18:14 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/23 10:49:17 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_cmd *cmd, t_exec *exec)
{
	int	status;

	status = 0;
	if (cmd->args[1] != NULL)
	{
		status = ft_atoi(cmd->args[1]);
		if (status < 0)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (-1);
		}
		if (cmd->args[2] != NULL)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (-1);
		}
	}
	exec->exit_status = (unsigned char)status;
	global_exit(exec);
	return (1);
}

void	global_exit(t_exec *exec)
{
	int	status;

	status = exec->exit_status;
	ft_free_cmd(exec->cmd);
	exec->cmd = NULL;
	unlink(exec->infile_path);
	unlink(exec->heredoc_path);
	free_env(exec->env);
	free(exec->infile_path);
	free(exec->heredoc_path);
	if (exec->liste)
		free_list(exec->liste);
	free(exec);
	exec = NULL;
	printf("exit\n");
	exit(status);
}
