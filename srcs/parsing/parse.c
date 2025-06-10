/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:17:16 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/10 16:05:31 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_parse(t_split *split, t_exec *exec)
{
	int	i;
	int	len_split;

	len_split = len_list(split);
	i = 0;
	while (split)
	{
		// if (!syntax_error(split->str, len_split, i + 1))
		// 	return (exec->exit_status = 2, 0);
		if (ft_strchr(DELIMITER, split->str[0])
			&& split->next && split->str[0] == split->next->str[0])
			return (printf("minishell : parse error near '%c'\n",
					split->str[0]), exec->exit_status = 2, 0);
		split = split->next;
		i++;
	}
	return (1);
}

int	syntax_error(char *split, int len_split, int position)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (len_split == position && ft_strchr(DELIMITER, split[i]))
			return (printf("minishell : parse error near '%c'\n", split[i]), 0);
		if (position == 1 && ft_strchr(DELIMITER2, split[i]) && !is_in_quotes(i,
				split))
			return (printf("minishell : parse error near '%c'\n", split[i]), 0);
		i++;
	}
	return (1);
}

int	parse_one_case(char *split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strchr(ERROR_CHAR, split[i]))
		{
			printf("Invalid syntax error\n");
			return (0);
		}
		i++;
	}
	return (1);
}
