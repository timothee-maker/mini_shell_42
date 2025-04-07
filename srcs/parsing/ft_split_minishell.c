/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:35:03 by lde-guil          #+#    #+#             */
/*   Updated: 2025/04/07 10:22:01 by tnolent          ###   ########.fr       */
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

int		count_world(char const *str, char sep);
int		is_sep(char c, char sep);
int		size_tab(const char *str, char sep);
void	quote_case(const char *s, t_split *split);
void	dollar_case(const char *s, t_split *split);

char	**ft_split(char const *s, char c)
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
		else if (!is_sep(s[split.i], c))
		{
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
	while (!is_sep(s[split->i], ' ') && s[split->i] && !is_sep(s[split->i], '\"'))
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
	split->result[split->k++][split->l] = '\0';
	split->l = 0;
}

int	count_world(char const *str, char sep)
{
	int	compteur;
	int	i;
	int	j;

	j = 0;
	i = 0;
	compteur = 1;
	while (str[i])
	{
		if (!is_sep(str[i], sep) && compteur == 1)
		{
			j++;
			compteur = 0;
		}
		else if (is_sep(str[i], sep) && compteur == 0)
			compteur = 1;
		i++;
	}
	return (j);
}

int	size_tab(char const *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && !is_sep(str[i], sep))
		i++;
	return (i);
}

// void	quote_case(const char *s, t_split *split)
// {
// 	split->tmp = s[split->i];
// 	split->i++;
// 	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 	split->result[split->k][split->l++] = s[split->i - 1];
// 	while (s[split->i])
// 	{
// 		if (s[split->i] != s[split->tmp])
// 		{
// 			if (s[split->i] == '$' && split->tmp == '\"')
// 			{
// 				split->result[split->k][split->l++] = '\"';
// 				split->result[split->k++][split->l] = '\0';
// 				dollar_case(s, split);
// 				split->result[split->k][split->l++] = '\"';
// 			}
// 			if (s[split->i])
// 				split->result[split->k][split->l++] = s[split->i++];
// 		}
// 	}
// 	if (s[split->i])
// 		split->result[split->k][split->l++] = s[split->i++];
// 	split->result[split->k++][split->l] = '\0';
// 	split->l = 0;
// }

// static void	ft_define_vars(size_t *i, int *j, int *s_word)
// {
// 	*i = 0;
// 	*j = 0;
// 	*s_word = -1;
// }

// static void	*ft_free(char **strs, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		free(strs[i]);
// 		i++;
// 	}
// 	free(strs);
// 	return (NULL);
// }

// static char	*ft_fill_word(const char *str, int start, int end)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	word = malloc((end - start + 1) * sizeof(char));
// 	if (!word)
// 		return (NULL);
// 	while (start < end)
// 	{
// 		word[i] = str[start];
// 		i++;
// 		start++;
// 	}
// 	word[i] = 0;
// 	return (word);
// }

// static int	ft_wcount(const char *str, char c)
// {
// 	int	wc;
// 	int	sep;

// 	wc = 0;
// 	sep = 0;
// 	while (*str)
// 	{
// 		if (*str != c && sep == 0)
// 		{
// 			sep = 1;
// 			wc++;
// 		}
// 		else if (*str == c)
// 			sep = 0;
// 		str++;
// 	}
// 	return (wc);
// }

// char	**ft_split(const char *s, char c)
// {
// 	char	**res;
// 	size_t	i;
// 	int		j;
// 	int		s_word;

// 	ft_define_vars(&i, &j, &s_word);
// 	res = ft_calloc((ft_wcount(s, c) + 1), sizeof(char *));
// 	if (!res)
// 		return (NULL);
// 	while (i <= ft_strlen(s))
// 	{
// 		if (s[i] != c && s_word < 0)
// 			s_word = i;
// 		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
// 		{
// 			res[j] = ft_fill_word(s, s_word, i);
// 			if (!(res[j]))
// 				return (ft_free(res, j));
// 			s_word = -1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }


