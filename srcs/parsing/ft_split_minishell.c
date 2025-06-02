/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:35:03 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/02 11:37:20 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*ft_split_list_minishell(const char *s, char sep)
{
	t_split_parse	split;

	init_split(&split);
	while (s[split.i])
	{
		if (ft_strchr(QUOTES, s[split.i]))
			handle_quote_case(s, &split);
		else if (s[split.i] == '$' && (!split.tmp || split.tmp == '\"'))
			handle_dollar_case(s, &split);
		else if (!is_sep(s[split.i], sep))
		{
			fill_list(&split, s, sep);
			flush_buffer(&split);
		}
		else
			split.i++;
	}
	return (flush_buffer(&split), split.head);
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
		strcpy(new_buf, split->buffer);
		free(split->buffer);
	}
	else
		new_buf[0] = '\0';
	new_buf[len] = c;
	new_buf[len + 1] = '\0';
	split->buffer = new_buf;
}

void	handle_dollar_case(const char *s, t_split_parse *split)
{
	int	start_context;

	if (split->tmp == '\'')
		start_context = 2;
	else if (split->tmp == '\"')
		start_context = 3;
	else
		start_context = 1;
	if (start_context == 1 || start_context == 3)
		flush_buffer(split);
	split->context = start_context;
	add_char(split, s[split->i++]);
	while (s[split->i] && !ft_strchr(NO_ENV, s[split->i]) && s[split->i] != '$')
		add_char(split, s[split->i++]);
	flush_buffer(split);
	split->context = 0;
}

void	handle_quote_case(const char *s, t_split_parse *split)
{
	split->tmp = s[split->i++];
	while (s[split->i] && s[split->i] != split->tmp)
	{
		if (s[split->i] == '$' && split->tmp != '\'')
		{
			split->is_in_quotes = 1;
			handle_dollar_case(s, split);
		}
		else
			add_char(split, s[split->i++]);
	}
	if (s[split->i])
		split->i++;
	split->is_in_quotes = 0;
	split->tmp = 0;
	if (s[split->i] && is_sep(s[split->i], ' '))
		flush_buffer(split);
}

// typedef struct s_split
// {
// 	int		i;
// 	int		k;
// 	int		l;
// 	int		dollar;
// 	int		tmp;
// 	char	**result;
// }	t_split;

// int		quote_case(const char *s, t_split *split);
// int		dollar_case(const char *s, t_split *split);
// int		init_split(t_split *split, char const *s);
// void	full_split(t_split *split, char const *s, char c);

// char	**ft_split_minishell(char const *s, char c)
// {
// 	t_split	split;

// 	if (!init_split(&split, s))
// 		return (free(split.result), NULL);
// 	while (s[split.i])
// 	{
// 		split.l = 0;
// 		if (ft_strchr(QUOTES, s[split.i]))
// 		{
// 			if (!quote_case(s, &split))
// 				return (NULL);
// 		}
// 		if (!is_sep(s[split.i], c))
// 		{
// 			if (split.l == 0)
// 				split.result[split.k] = malloc(sizeof(char) * (ft_strlen(s)
// + 1));
// 			if (!split.result[split.k])
// 				return ((free_split(split.result), NULL));
// 			full_split(&split, s, c);
// 			split.result[split.k++][split.l] = '\0';
// 		}
// 		else
// 			split.i++;
// 	}
// 	return (split.result[split.k] = NULL, split.result);
// }

// void	full_split(t_split *split, char const *s, char c)
// {
// 	while (!is_sep(s[split->i], c) && s[split->i])
// 	{
// 		if (split->tmp == s[split->i])
// 			split->tmp = 0;
// 		else if (ft_strchr(QUOTES, s[split->i]) && split->tmp == 0)
// 			split->tmp = s[split->i];
// 		if (ft_strchr(NO_ENV, s[split->i]) && split->dollar == 1)
// 		{
// 			split->dollar = 0;
// 			break ;
// 		}
// 		if (is_sep(s[split->i], '$') && (split->tmp == '\"' || split->tmp == 0)
// && split->dollar == 0)
// 		{
// 			split->dollar = 1;
// 			break ;
// 		}
// 		split->result[split->k][split->l++] = s[split->i++];
// 	}
// }

// int		init_split(t_split *split, char const *s)
// {
// 	split->i = 0;
// 	split->k = 0;
// 	split->tmp = 0;
// 	split->dollar = 0;
// 	split->result = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
// 	if (!split->result)
// 		return (0);
// 	return (1);
// }

// int		quote_case(const char *s, t_split *split)
// {
// 	split->tmp = s[split->i++];
// 	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 	if (!split->result[split->k])
// 		return (free_split(split->result), 0);
// 	split->result[split->k][split->l++] = split->tmp;
// 	while (s[split->i] && s[split->i] != split->tmp)
// 	{
// 		if (s[split->i] == '$' && split->tmp != '\'')
// 			dollar_case(s, split);
// 		split->result[split->k][split->l++] = s[split->i++];
// 	}
// 	if (s[split->i])
// 		split->result[split->k][split->l++] = s[split->i++];
// 	if (is_sep(s[split->i], ' ') || s[split->i] == '$')
// 	{
// 		split->result[split->k++][split->l] = '\0';
// 		split->l = 0;
// 	}
// 	split->tmp = 0;
// 	return (1);
// }

// int		dollar_case(const char *s, t_split *split)
// {
// 	split->result[split->k][split->l++] = '\"';
// 	split->result[split->k++][split->l] = '\0';
// 	split->l = 0;
// 	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 	if (!split->result[split->k])
// 		return (free_split(split->result), 0);
// 	while (!ft_strchr(NO_ENV, s[split->i]) && s[split->i]
// && !is_sep(s[split->i], '\''))
// 	{
// 		split->result[split->k][split->l++] = s[split->i++];
// 		if (is_sep(s[split->i], '$'))
// 		{
// 			split->result[split->k++][split->l] = '\0';
// 			split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 			if (!split->result[split->k])
// 				return (free_split(split->result), 0);
// 			split->l = 0;
// 		}
// 	}
// 	split->result[split->k++][split->l] = '\0';
// 	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 	if (!split->result[split->k])
// 		return (free_split(split->result), 0);
// 	split->l = 0;
// 	split->result[split->k][split->l++] = '\"';
// 	return (1);
// }
