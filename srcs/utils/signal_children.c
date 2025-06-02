/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:21:31 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/30 12:22:11 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
}

static void	hdoc_handler(int sig)
{
	(void)sig;
	exit_hdoc(NULL);
	exit(130);
}

void	hdoc_signals(void)
{
	signal(SIGINT, &hdoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	child_hdoc(t_exec *exec, t_element *elem)
{
	hdoc_signals();
	exit_hdoc(exec);
	if (!read_hdoc(exec, elem->arg))
	{
		free_exec(exec);
		exit(1);
	}
	free_exec(exec);
	exit(0);
}

void	exit_hdoc(t_exec *exec)
{
	static t_exec	*backup;

	if (exec)
		backup = exec;
	else if (exec == NULL && backup)
	{
		free_exec(backup);
	}
}
