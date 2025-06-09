/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:06:33 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/03 11:40:12 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	args_loop(t_element *elem, t_exec *exec, char sep)
{
	char	*temp;

	while (elem)
	{
		temp = NULL;
		if (elem->arg)
			temp = ft_strdup(elem->arg);
		if (!ft_strcmp(elem->token, "ARG") || !ft_strcmp(elem->token,
				"ARG-INQUOTE"))
		{
			ft_putstr_fd(temp, exec->infile);
			if ((elem->next && ft_strcmp(elem->next->token, "ARG-INQUOTE"))
				&& ft_strcmp(elem->token, "ARG-INQUOTE"))
				write(exec->infile, &sep, 1);
		}
		elem = elem->next;
		if (temp)
			free(temp);
	}
}
