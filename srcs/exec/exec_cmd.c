/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:14:46 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/12 11:47:08 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_loop(t_exec *exec)
{
	t_cmd	*cmd;

	cmd = exec->cmd;
	while (cmd)
	{
		if (cmd->pid != 0)
			wait_status(exec, cmd);
		cmd = cmd->next;
		g_signal_pid = 0;
	}
}

int	exec_line(t_exec *exec, t_list *list)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!fill_cmd(list, exec, cmd))
		return (0);
	reopen_io(exec);
	cmd = exec->cmd;
	while (cmd)
	{
		if (pipe(exec->pipe) == -1)
			return (perror("Pipe error"), 1);
		if (is_single_builtin(cmd))
			exec_single_builtin(cmd, exec);
		else
			ft_fork(exec, cmd);
		cmd = cmd->next;
	}
	wait_loop(exec);
	ft_free_cmd(exec->cmd);
	exec->cmd = NULL;
	return (1);
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
		{
			exec->exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
			exec->exit_status = WTERMSIG(status) + 128;
	}
}

int	exec_cmd(t_exec *exec, t_cmd *cmd)
{
	int	status;

	if (cmd->is_builtin)
	{
		status = exec_builtin(exec, cmd);
		return (free_exec(exec), status);
	}
	else if (cmd->path == NULL)
	{
		ft_putstr_fd("Command not found", 2);
		if (cmd->name)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->name, 2);
		}
		ft_putstr_fd("\n", 2);
		return (free_exec(exec), 127);
	}
	else if (execve(cmd->path, cmd->args, str_env(exec)) == -1)
	{
		exec->exit_status = 1;
		perror("Execve error");
		return (free_exec(exec), 2);
	}
	return (0);
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
