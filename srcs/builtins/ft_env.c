/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:28:52 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/30 13:14:25 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec *exec)
{
	t_env	*var;

	var = exec->env;
	while (var != NULL)
	{
		if (var->name != NULL && var->value != NULL)
		{
			printf("%s", var->name);
			printf("=%s\n", var->value);
		}
		var = var->next;
	}
	return (exec->exit_status = 0, 0);
}
