/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:18:02 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/30 12:55:02 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_input(char *input, char *delimit)
{
	if (input[0] == '\0')
		return (1);
	if (ft_strcmp(input, delimit))
		return (1);
	return (0);
}

int	no_hdoc_case(char *delimit)
{
	printf("minishell : warning: here-document ");
	printf("delimited by end-of-file (wanted '%s')\n", delimit);
	return (1);
}

int	read_hdoc(t_exec *exec, char *delimit)
{
	char	*input;

	close(exec->heredoc);
	exec->heredoc = open(exec->heredoc_path, O_RDWR | O_TRUNC, 0777);
	if (exec->heredoc == -1)
		return (perror("Error opening heredoc file"), 0);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (no_hdoc_case(delimit));
		if (!check_input(input, delimit))
			break ;
		ft_putendl_fd(input, exec->heredoc);
		free(input);
	}
	free(input);
	close(exec->heredoc);
	exec->heredoc = open(exec->heredoc_path, O_RDWR);
	return (1);
}

static int	fork_hdoc(t_exec *exec, t_element *elem)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, parent_hdoc);
	if (pid < 0)
	{
		perror("Fork failed");
		free_exec(exec);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_hdoc(exec, elem);
	else
	{
		waitpid(pid, &exec->exit_status, 0);
		if (exec->exit_status == 33280)
			return (prompt_sig(), 130);
		else
			return (prompt_sig(), 0);
	}
	return (prompt_sig(), 0);
}

int	fill_heredoc(t_list *list, t_exec *exec)
{
	t_element	*elem;
	t_element	*temp;

	if (g_signal_pid == 130)
		return (0);
	elem = list->first;
	while (elem)
	{
		if (!ft_strcmp(elem->token, "HERE-DOC"))
		{
			temp = elem->next;
			exec->exit_status = fork_hdoc(exec, temp);
			if (exec->exit_status == 130)
				return (3);
		}
		elem = elem->next;
	}
	return (0);
}
