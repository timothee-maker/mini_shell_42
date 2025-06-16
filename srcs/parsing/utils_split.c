/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:31:49 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/16 17:10:09 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_new_split_node(t_split *new, t_split_parse *split)
{
	new->next = NULL;
	new->is_in_quotes = 0;
	new->context = 0;
	if (split->is_in_quotes == 1)
		new->is_in_quotes = 1;
	if (split->context != 0)
		new->context = split->context;
}

void	append_to_list(t_split_parse *split, const char *content)
{
	t_split	*new;

	new = malloc(sizeof(t_split));
	if (!new)
		return ;
	new->str = ft_strdup(content);
	init_new_split_node(new, split);
	if (!split->head)
		split->head = new;
	else
		split->tail->next = new;
	split->tail = new;
}

void	flush_buffer(t_split_parse *split)
{
	if (split->buffer && split->buffer[0])
	{
		append_to_list(split, split->buffer);
		if (split->heredocs == 1)
			split->heredocs = 0;
		if (!ft_strcmp("<<", split->buffer))
			split->heredocs = 1;
	}
	free(split->buffer);
	split->buffer = NULL;
}

void	fill_list(t_split_parse *split, const char *s, char c, t_exec *exec)
{
	while (s[split->i] && !is_sep(s[split->i], c))
	{
		if (ft_strchr(QUOTES, s[split->i]))
			handle_quote_case(s, split, exec);
		else if (s[split->i] == '$' && (!split->tmp || split->tmp == '\"')
			&& split->heredocs == 0)
			handle_dollar_case(s, split, exec);
		else
			add_char(split, s[split->i++]);
	}
}
