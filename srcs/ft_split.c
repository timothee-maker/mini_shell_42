/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:53 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/19 15:40:13 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define QUOTES "\'\""

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
char	*ft_strndup(const char *s1, size_t size);
void	quote_case(const char *s, t_split *split);

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

void	quote_case(const char *s, t_split *split)
{
	int	len;

	len = 0;
	split->tmp = split->i;
	split->i++;
	split->result[split->k] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	split->result[split->k][split->l++] = s[split->i - 1];
	while (s[split->i] != s[split->tmp] && s[split->i])
		split->result[split->k][split->l++] = s[split->i++];
	if (s[split->i])
		split->result[split->k][split->l++] = s[split->i++];
	split->result[split->k++][split->l] = '\0';
	split->l = 0;
}

int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
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

// void	print_tab(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != 0)
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// }

// int	main(int ac, char **av)
// {
// 	char *str = "<}|>";
// 	char **ptr;
// 	int i = 0;
// 	ptr = ft_split(str, ' ');
// 	print_tab(ptr);
// 	while (ptr[i] != NULL)
// 		free(ptr[i++]);
// 	free(ptr);
// }