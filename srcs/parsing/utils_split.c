/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:31:49 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/19 16:09:00 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_split(t_split_parse *split)
{
	split->i = 0;
	split->tmp = 0;
	split->dollar = 0;
	split->is_in_quotes = 0;
	split->env_context = 0;
	split->buffer = NULL;
	split->head = NULL;
	split->tail = NULL;
}

void	append_to_list(t_split_parse *split, const char *content)
{
	t_split	*new;

	new = malloc(sizeof(t_split));
	if (!new)
		return ;
	new->str = ft_strdup(content);
	new->next = NULL;
	new->is_in_quotes = 0;
	new->env_context = 0;
	if (split->is_in_quotes == 1)
		new->is_in_quotes = 1;
	if (split->env_context != 0)
		new->env_context = split->env_context;
	if (!split->head)
		split->head = new;
	else
		split->tail->next = new;
	split->tail = new;
}

void	flush_buffer(t_split_parse *split)
{
	if (split->buffer && split->buffer[0])
		append_to_list(split, split->buffer);
	free(split->buffer);
	split->buffer = NULL;
}

void	fill_list(t_split_parse *split, const char *s, char c)
{
	while (s[split->i] && !is_sep(s[split->i], c))
	{
		if (ft_strchr(QUOTES, s[split->i]))
			handle_quote_case(s, split);
		else if (s[split->i] == '$' && (!split->tmp || split->tmp == '\"'))
			handle_dollar_case(s, split);
		else
			add_char(split, s[split->i++]);
	}
}
