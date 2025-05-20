/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:28:52 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/20 09:28:55 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_exec *exec)
{
	t_env	*var;

	var = exec->env;
	while (var != NULL)
	{
		if (var->name != NULL && var->value != NULL)
			printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
	return (0);
}
