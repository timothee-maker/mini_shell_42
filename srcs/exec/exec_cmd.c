/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:14:46 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/30 13:33:12 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_loop(t_exec *exec)
{
	t_cmd	*cmd;

	cmd = exec->cmd;
	while (cmd)
	{
		if (cmd->pid != 0 && cmd->to_exec == 1)
			wait_status(exec, cmd);
		cmd = cmd->next;
		g_signal_pid = 0;
	}
}

int	exec_line(t_exec *exec, t_list *list)
{
	t_cmd	*cmd;

	cmd = NULL;
	fill_cmd(list, exec, cmd);
	reopen_io(exec);
	cmd = exec->cmd;
	while (cmd)
	{
		if (cmd->to_exec == 1)
		{
			if (pipe(exec->pipe) == -1)
				return (perror("Pipe error"), 1);
			if (is_single_builtin(cmd))
				exec_single_builtin(cmd, exec);
			else
				ft_fork(exec, cmd);
		}
		cmd = cmd->next;
	}
	if (exec->pipe[0])
		close(exec->pipe[0]);
	if (exec->pipe[1])
		close(exec->pipe[1]);
	wait_loop(exec);
	return (ft_free_cmd(exec->cmd), exec->cmd = NULL, 1);
}

void	wait_status(t_exec *exec, t_cmd *cmd)
{
	int	status;
	int	pid;

	status = 0;
	pid = waitpid(cmd->pid, &status, 0);
	if (pid == cmd->pid)
	{
		if (WIFEXITED(status))
			exec->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exec->exit_status = WTERMSIG(status) + 128;
	}
}

int	exec_builtin(t_exec *ex, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
		return (ft_cd(ex, cmd));
	else if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
		return (ft_echo(ex, cmd));
	else if (!ft_strncmp(cmd->name, "env", ft_strlen(cmd->name)))
		return (ft_env(ex));
	else if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
		return (ft_exit(cmd, ex));
	else if (!ft_strncmp(cmd->name, "export", ft_strlen(cmd->name)))
		return (ft_export(ex, cmd));
	else if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
		return (ft_pwd(ex, cmd));
	else if (!ft_strncmp(cmd->name, "unset", ft_strlen(cmd->name)))
		return (ft_unset(ex, cmd));
	else
		return (2);
}
