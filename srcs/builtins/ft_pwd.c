/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:06:05 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/10 15:47:57 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_exec *exec, t_cmd *cmd)
{
    (void) cmd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (exec->exit_status = 0, 0);
	}
	else
	{
		ft_putendl_fd("pwd: cannot access current directory", 2);
		return (exec->exit_status = 1, 2);
	}
}
