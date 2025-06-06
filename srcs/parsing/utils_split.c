/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:31:49 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/06 13:39:59 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value_for_content(const char *content, t_exec *exec)
{
	char	*value;

	value = NULL;
	if (!ft_strcmp(content, "$"))
		return (ft_strdup("$"));
	else if (!ft_strcmp(content, "$?"))
		return (ft_itoa(exec->exit_status));
	else
	{
		value = fetch_value((char *)content, exec);
		if (value)
			return (value);
		else
			return (ft_strdup(""));
	}
}

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

void	append_to_list(t_split_parse *split, const char *content, t_exec *exec)
{
	t_split	*new;

	new = malloc(sizeof(t_split));
	if (!new)
		return ;
	if (content[0] == '$' && content[1] != '\0' && split->tmp == '\"')
		new->str = get_env_value_for_content(content, exec);
	else
		new->str = ft_strdup(content);
	init_new_split_node(new, split);
	if (!split->head)
		split->head = new;
	else
		split->tail->next = new;
	split->tail = new;
}

void	flush_buffer(t_split_parse *split, t_exec *exec)
{
	if (split->buffer && split->buffer[0])
		append_to_list(split, split->buffer, exec);
	free(split->buffer);
	split->buffer = NULL;
}

void	fill_list(t_split_parse *split, const char *s, char c, t_exec *exec)
{
	while (s[split->i] && !is_sep(s[split->i], c))
	{
		if (ft_strchr(QUOTES, s[split->i]))
			handle_quote_case(s, split, exec);
		else if (s[split->i] == '$' && (!split->tmp || split->tmp == '\"'))
			handle_dollar_case(s, split, exec);
		else
			add_char(split, s[split->i++]);
	}
}
