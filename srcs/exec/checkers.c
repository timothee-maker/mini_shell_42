/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:19:15 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/20 09:19:20 by lde-guil         ###   ########.fr       */
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
	if (cmd->output >= 0)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->output);
	}
	exec_builtin(exec, cmd);
}
