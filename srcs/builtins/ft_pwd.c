/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:06:05 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/20 15:06:07 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	if (cmd->args[1] != NULL)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		return (2);
	}
	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		ft_putendl_fd("pwd: cannot access current directory", 2);
		return (2);
	}
}
