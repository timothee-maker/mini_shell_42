/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:21:46 by tnolent           #+#    #+#             */
/*   Updated: 2025/11/09 22:45:44 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigint(int code)
{
	(void)code;
	printf("\n");
	clear_rl_line();
	if (g_signal_pid >= 0 && g_signal_pid <= 130)
		rl_redisplay();
	g_signal_pid = 130;
}

void	parent_hdoc(int code)
{
	(void)code;
	printf("\n");
	g_signal_pid = 130;
}

void	prompt_sig(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}
