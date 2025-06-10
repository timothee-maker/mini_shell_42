/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:35:03 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/06 15:37:02 by tnolent          ###   ########.fr       */
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
		else if (s[split.i] == '$' && (!split.tmp || split.tmp == '\"'))
			handle_dollar_case(s, &split, exec);
		else if (!is_sep(s[split.i], ' '))
		{
			fill_list(&split, s, ' ', exec);
			flush_buffer(&split, exec);
		}
		else
			split.i++;
	}
	flush_buffer(&split, exec);
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
	new_buf = malloc(len + 2);
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
	char	*value;
	int		j;

	j = 0;
	value = NULL;
	if (!ft_strcmp(var_name, "$"))
		value = ft_strdup("$");
	else if (!ft_strcmp(var_name, "$?"))
		value = ft_itoa(exec->exit_status);
	else
	{
		value = fetch_value(var_name, exec);
	}
	if (!value)
		value = ft_strdup(" ");
	if (value)
	{
		while (value[j])
			add_char(split, value[j++]);
		free(value);
	}
}

void	handle_dollar_case(const char *s, t_split_parse *split, t_exec *exec)
{
	int		start;
	int		len;
	char	*var_name;

	start = split->i + 1;
	len = 0;
	while (s[start + len] && !ft_strchr(NO_ENV, s[start + len]) && s[start
		+ len] != '$')
		len++;
	if (len == 0)
	{
		add_char(split, s[split->i++]);
		return ;
	}
	var_name = malloc(len + 2);
	if (!var_name)
		return ;
	var_name[0] = '$';
	ft_strncpy(var_name + 1, s + split->i + 1, len);
	var_name[len + 1] = '\0';
	handle_dollar_value(var_name, split, exec);
	free(var_name);
	split->i += len + 1;
	if (s[split->i] == ' ' && split->tmp == 0)
		flush_buffer(split, exec);
}

void	handle_quote_case(const char *s, t_split_parse *split, t_exec *exec)
{
	split->tmp = s[split->i++];
	while (s[split->i] && s[split->i] != split->tmp)
	{
		if (s[split->i] == '$' && split->tmp != '\'')
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
	if (s[split->i] && is_sep(s[split->i], ' '))
		flush_buffer(split, exec);
}
