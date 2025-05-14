/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:35:03 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/14 11:41:37 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_split
{
	int		i;
	int		k;
	int		l;
	int		dollar;
	int		tmp;
	char	**result;
}	t_split;

int		quote_case(const char *s, t_split *split);
int		dollar_case(const char *s, t_split *split);
int		init_split(t_split *split, char const *s);
void	full_split(t_split *split, char const *s, char c);

char	**ft_split_minishell(char const *s, char c)
{
	t_split	split;

	if (!init_split(&split, s))
		return (free(split.result), NULL);
	while (s[split.i])
	{
		split.l = 0;
		if (ft_strchr(QUOTES, s[split.i]))
		{
			if (!quote_case(s, &split))
				return (NULL);
		}
		if (!is_sep(s[split.i], c))
		{
			if (split.l == 0)
				split.result[split.k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
			if (!split.result[split.k])
				return ((free_split(split.result), NULL));
			full_split(&split, s, c);
			split.result[split.k++][split.l] = '\0';
		}
		else
			split.i++;
	}
	return (split.result[split.k] = NULL, split.result);
}

void	full_split(t_split *split, char const *s, char c)
{
	while (!is_sep(s[split->i], c) && s[split->i])
	{
		if (split->tmp == s[split->i])
			split->tmp = 0;
		else if (ft_strchr(QUOTES, s[split->i]) && split->tmp == 0)
			split->tmp = s[split->i];
		if (ft_strchr(NO_ENV, s[split->i]) && split->dollar == 1)
		{
			split->dollar = 0;
			break;
		}
		if (is_sep(s[split->i], '$') && (split->tmp == '\"' || split->tmp == 0) && split->dollar == 0)
		{
			split->dollar = 1;
			break;
		}
		split->result[split->k][split->l++] = s[split->i++];
	}
}

int		init_split(t_split *split, char const *s)
{
	split->i = 0;
	split->k = 0;
	split->tmp = 0;
	split->dollar = 0;
	split->result = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!split->result)
		return (0);
	return (1);
}

int		quote_case(const char *s, t_split *split)
{
	split->tmp = s[split->i++];
	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!split->result[split->k])
		return (free_split(split->result), 0); 
	split->result[split->k][split->l++] = split->tmp;
	while (s[split->i] && s[split->i] != split->tmp)
	{
		if (s[split->i] == '$' && split->tmp != '\'')
			dollar_case(s, split);
		split->result[split->k][split->l++] = s[split->i++];
	}
	if (s[split->i])
		split->result[split->k][split->l++] = s[split->i++];
	if (is_sep(s[split->i], ' ') || s[split->i] == '$')
	{
		split->result[split->k++][split->l] = '\0';
		split->l = 0;
	}
	split->tmp = 0;
	return (1);
}

int		dollar_case(const char *s, t_split *split)
{
	split->result[split->k][split->l++] = '\"';
	split->result[split->k++][split->l] = '\0';
	split->l = 0;
	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!split->result[split->k])
		return (free_split(split->result), 0); 
	while (!ft_strchr(NO_ENV, s[split->i]) && s[split->i] && !is_sep(s[split->i], '\''))
	{
		split->result[split->k][split->l++] = s[split->i++];
		if (is_sep(s[split->i], '$'))
		{
			split->result[split->k++][split->l] = '\0';  
			split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
			if (!split->result[split->k])
				return (free_split(split->result), 0);
			split->l = 0;
		}
	}
	split->result[split->k++][split->l] = '\0';  
	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!split->result[split->k])
		return (free_split(split->result), 0);
	split->l = 0;
	split->result[split->k][split->l++] = '\"';
	return (1);
}
