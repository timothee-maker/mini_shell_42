/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:35:03 by lde-guil          #+#    #+#             */
/*   Updated: 2025/04/17 14:40:32 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_split
{
	int		i;
	int		k;
	int		l;
	int		tmp;
	char	**result;
}	t_split;

void	quote_case(const char *s, t_split *split);
void	dollar_case(const char *s, t_split *split);

char	**ft_split_minishell(char const *s, char c)
{
	t_split	split;

	split.i = 0;
	split.k = 0;
	split.result = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!split.result || !s)
		return (NULL);
	while (s[split.i])
	{
		split.l = 0;
		if (ft_strchr(QUOTES, s[split.i]))
			quote_case(s, &split);
		if (!is_sep(s[split.i], c))
		{
			if (split.l == 0)
				split.result[split.k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
			while (!is_sep(s[split.i], c) && s[split.i])
				split.result[split.k][split.l++] = s[split.i++];
			split.result[split.k++][split.l] = '\0';
		}
		else
			split.i++;
	}
	return (split.result[split.k] = NULL, split.result);
}

void	dollar_case(const char *s, t_split *split)
{
	split->result[split->k][split->l++] = '\"';
	split->result[split->k++][split->l] = '\0';
	split->l = 0;
	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (!is_sep(s[split->i], ' ') && s[split->i] && !is_sep(s[split->i], '\"') && !is_sep(s[split->i], '$'))
		split->result[split->k][split->l++] = s[split->i++];
	split->result[split->k++][split->l] = '\0';  
	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!split->result)
		exit(EXIT_FAILURE);
	split->l = 0;
	split->result[split->k][split->l++] = '\"';
}

void	quote_case(const char *s, t_split *split)
{
	split->tmp = s[split->i++];
	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!split->result[split->k])
		exit(EXIT_FAILURE);
	split->result[split->k][split->l++] = split->tmp;
	while (s[split->i] && s[split->i] != split->tmp)
	{
		if (s[split->i] == '$' && split->tmp == '\"')
			dollar_case(s, split);
		split->result[split->k][split->l++] = s[split->i++];
	}
	if (s[split->i])
		split->result[split->k][split->l++] = s[split->i++];
	if (is_sep(s[split->i], ' '))
	{
		split->result[split->k++][split->l] = '\0';
		split->l = 0;
	}
}

// void	quote_case(const char *s, t_split *split)
// {
// 	split->tmp = s[split->i++];  // quote char ('"' or '\'')
// 	if (!split->result[split->k])
// 	{
// 		split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 		if (!split->result[split->k])
// 			exit(EXIT_FAILURE);
// 	}

// 	split->result[split->k][split->l++] = split->tmp;  // opening quote

// 	while (s[split->i] && s[split->i] != split->tmp)
// 	{
// 		if (s[split->i] == '$' && split->tmp == '\"')
// 			dollar_case(s, split);  // handle $ inside double quotes
// 		split->result[split->k][split->l++] = s[split->i++];
// 	}

// 	if (s[split->i] == split->tmp)  // closing quote
// 		split->result[split->k][split->l++] = s[split->i++];

// 	// ⚠️ NE PAS fermer la string ici si le mot continue après
// 	// On ne fait pas de k++ ici, sauf si c'est suivi d'un séparateur

// 	if (is_sep(s[split->i], ' ') || s[split->i] == '\0')
// 	{
// 		split->result[split->k][split->l] = '\0';
// 		split->k++;
// 		split->l = 0;
// 	}
// }

