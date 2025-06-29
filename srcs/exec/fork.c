/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:16:19 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/27 09:46:45 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_dup2(int file, int std, t_exec *exec)
{
	if (dup2(file, std) == -1)
	{
		perror("dup error");
		global_exit(exec, 2);
	}
	return (1);
}

void	ft_fork(t_exec *exec, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	g_signal_pid = pid;
	if (pid < 0)
	{
		perror("Fork error");
		return ;
	}
	if (pid > 0)
	{
		cmd->pid = pid;
		parent_process(cmd, exec->pipe);
	}
	else
		child_process(cmd, exec->pipe, exec);
	return ;
}

void	child_process(t_cmd *cmd, int pipe[2], t_exec *exec)
{
	close(pipe[0]);
	if (cmd->heredoc_content && cmd->input < 0)
	{
		reopen_io(exec);
		ft_putstr_fd(cmd->heredoc_content, exec->heredoc);
		reopen_io(exec);
		ft_dup2(exec->heredoc, STDIN_FILENO, exec);
	}
	else if (cmd->input >= 0)
	{
		ft_dup2(cmd->input, STDIN_FILENO, exec);
		close(cmd->input);
	}
	if (cmd->output >= 0)
	{
		ft_dup2(cmd->output, STDOUT_FILENO, exec);
		close(cmd->output);
	}
	else if (cmd->next != NULL)
		ft_dup2(pipe[1], STDOUT_FILENO, exec);
	close(pipe[1]);
	default_sig();
	exit(exec_cmd(exec, cmd));
}

void	parent_process(t_cmd *cmd, int pipe[2])
{
	close(pipe[1]);
	if (cmd->input >= 0)
		close(cmd->input);
	if (cmd->input == -1)
		cmd->input = pipe[0];
	if (cmd->next != NULL && cmd->next->input == -1
		&& cmd->next->heredoc_content == NULL)
		cmd->next->input = pipe[0];	
}
