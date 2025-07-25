/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:35:03 by lde-guil          #+#    #+#             */
/*   Updated: 2025/07/21 15:51:53 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*ft_split_list_minishell(const char *s, t_exec *exec)
{
	t_split_parse	split;

	init_split(&split);
	while (s[split.i])
	{
		if (ft_strchr(QUOTES, s[split.i]))
			handle_quote_case(s, &split, exec);
		else if (s[split.i] == '$' && (!split.tmp || split.tmp == '\"')
			&& split.heredocs == 0)
			handle_dollar_case(s, &split, exec);
		else if (!is_sep(s[split.i], ' ')
			&& !ft_strchr(WHITE_SPACE, s[split.i]))
		{
			fill_list(&split, s, ' ', exec);
			flush_buffer(&split);
		}
		else
			split.i++;
	}
	flush_buffer(&split);
	return (split.head);
}

void	add_char(t_split_parse *split, char c)
{
	int		len;
	char	*new_buf;

	if (split->buffer)
		len = ft_strlen(split->buffer);
	else
		len = 0;
	new_buf = ft_malloc(sizeof(char) * (len + 2), 1, NULL);
	if (!new_buf)
		return ;
	if (split->buffer)
	{
		ft_strncpy(new_buf, split->buffer, ft_strlen(split->buffer));
		free(split->buffer);
	}
	else
		new_buf[0] = '\0';
	new_buf[len] = c;
	new_buf[len + 1] = '\0';
	split->buffer = new_buf;
}

static void	handle_dollar_value(char *var_name, t_split_parse *split,
		t_exec *exec)
{
	char	**split_value;
	char	*value;
	int		i;

	i = 0;
	split_value = NULL;
	value = NULL;
	if (!ft_strcmp(var_name, "$"))
		value = ft_strdup("$");
	else if (!ft_strncmp(var_name, "$?", 2))
		value = ft_itoa(exec->exit_status);
	else
		value = fetch_value(var_name, exec);
	if (!value || value[0] == '\0')
	{
		free(value);
		return ;
	}
	split_value = ft_split(value, ' ');
	free(value);
	while (split_value[i])
		re_fill_list(split, split_value[i++], len_tab(split_value));
	free_tab(split_value);
}

void	handle_dollar_case(const char *s, t_split_parse *split, t_exec *exec)
{
	char	*var_name;

	var_name = extract_var_name(s, &split->i);
	if (!var_name)
	{
		add_char(split, s[split->i++]);
		return ;
	}
	handle_dollar_value(var_name, split, exec);
	free(var_name);
	if (s[split->i] == ' ' && split->tmp == 0)
		flush_buffer(split);
}

void	handle_quote_case(const char *s, t_split_parse *split, t_exec *exec)
{
	split->tmp = s[split->i++];
	while (s[split->i] && s[split->i] != split->tmp)
	{
		if (s[split->i] == '$' && split->tmp != '\'' && split->heredocs == 0)
		{
			split->is_in_quotes = 1;
			handle_dollar_case(s, split, exec);
		}
		else
			add_char(split, s[split->i++]);
	}
	if (s[split->i])
		split->i++;
	split->is_in_quotes = 0;
	split->tmp = 0;
	split->context = 1;
	if (s[split->i] && is_sep(s[split->i], ' '))
		flush_buffer(split);
}
