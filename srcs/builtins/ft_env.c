/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:28:52 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/12 11:41:54 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec *exec)
{
	t_env	*var;

	var = exec->env;
	while (var != NULL)
	{
		if (var->name != NULL)
			printf("%s", var->name);
		if (var->value != NULL)
			printf("=%s\n", var->value);
		else
			printf("\n");
		var = var->next;
	}
	return (exec->exit_status = 0, 0);
}
