/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:43:31 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/06 11:47:44 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr2(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str1[i] == str2[j++])
				return (1);
		}
		i++;
	}
	return (0);
}

void	empty_string_case(char *split, t_list *list, t_token *token)
{
	if (ft_strlen(split) == 0)
		return ;
	free(token->split->str);
	add_token(list, "ARG", token);
}

void	init_token(t_token *token)
{
	token->position = 0;
	token->redir = 0;
}

void	init_split(t_split_parse *split)
{
	split->i = 0;
	split->tmp = 0;
	split->dollar = 0;
	split->is_in_quotes = 0;
	split->context = 0;
	split->buffer = NULL;
	split->head = NULL;
	split->tail = NULL;
}

void	free_split(t_split *split)
{
	t_split	*current_split;
	t_split	*next;

	current_split = split;
	while (current_split)
	{
		next = current_split->next;
		free(current_split->str);
		free(current_split);
		current_split = next;
	}
}
