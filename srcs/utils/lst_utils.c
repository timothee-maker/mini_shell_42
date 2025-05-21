/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:23:19 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/21 09:23:21 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_end_env(t_env *env, t_env *var)
{
	t_env	*current;

	current = env;
	while (current->next)
	{
		current = current->next;
	}
	current->next = var;
	printf("added var at the end (%s\n)", var->name);
}
