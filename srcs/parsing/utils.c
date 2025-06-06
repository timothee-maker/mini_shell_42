/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:52:42 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/06 11:48:45 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_tab(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	len_list(t_split *split)
{
	int	i;

	i = 0;
	while (split)
	{
		i++;
		split = split->next;
	}
	return (i);
}
