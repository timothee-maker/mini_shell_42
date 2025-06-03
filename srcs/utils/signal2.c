/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:54:46 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/02 15:00:11 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
}

void	default_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	restore_signals(void)
{
	prompt_sig();
}

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}
