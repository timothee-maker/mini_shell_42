/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:18:14 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/28 17:09:56 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_str(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_number(char *str)
{
	int				i;
	int				sign;
	unsigned long	val;

	i = 0;
	sign = 1;
	val = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	if (!is_numeric_str(str))
		return (-1);
	while (str[i])
	{
		val = val * 10 + (str[i] - '0');
		if ((sign == 1 && val > 9223372036854775807UL) || (sign == -1
				&& val > 9223372036854775808UL))
			return (-1);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_exec *exec)
{
	int	status;

	status = 0;
	if (cmd->args[1] != NULL)
	{
		status = valid_number(cmd->args[1]);
		if (status == 1)
			status = ft_atoi(cmd->args[1]);
		if (status == -1)
		{
			if (cmd->args[2] == NULL)
				printf("minishell: exit: %s: numeric argument required\n",
					cmd->args[1]);
			status = 2;
		}
		if (cmd->args[2] != NULL)
			return (ft_putendl_fd("exit: too many arguments", 2), 1);
	}
	if (!cmd->prev && !cmd->next)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	global_exit(exec, (unsigned char)status);
	return (1);
}

void	global_exit(t_exec *exec, int status)
{
	ft_free_cmd(exec->cmd);
	exec->cmd = NULL;
	close(exec->infile);
	close(exec->heredoc);
	unlink(exec->infile_path);
	unlink(exec->heredoc_path);
	free_env(exec->env);
	free(exec->infile_path);
	free(exec->heredoc_path);
	if (exec->liste)
	{
		free_list(exec, exec->liste);
	}
	free(exec);
	exec = NULL;
	exit(status);
}
