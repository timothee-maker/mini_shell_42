/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:18:02 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/22 15:23:00 by tnolent          ###   ########.fr       */
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

static int	read_hdoc(t_exec *exec, char *delimit)
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

void	fill_heredoc(t_list *list, t_exec *exec)
{
	t_element	*elem;
	pid_t		pid;
	int			status;

	elem = list->first;
	while (elem)
	{
		if (!ft_strncmp(elem->token, "HERE-DOC", ft_strlen(elem->token)))
		{
			elem = elem->next;
			if (!ft_strncmp(elem->token, "DELIMITER", ft_strlen(elem->token)))
			{
				pid = fork();
				if (pid == 0)
					child_hdoc(exec, elem);
				waitpid(pid, &status, 0);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					g_exit_status = 130;
					return ;
				}
			}
		}
		elem = elem->next;
	}
}

void	child_hdoc(t_exec *exec, t_element *elem)
{
	signal(SIGINT, SIG_DFL);
	if (!read_hdoc(exec, elem->arg))
		exit(1);
	exit(0);
}
