/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:53 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/21 11:54:37 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_world(char const *str, char sep);
int		is_sep(char c, char sep);
int		size_tab(const char *str, char sep);
char	*ft_strndup(const char *s1, size_t size);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		l;
	char	**result;

	i = 0;
	k = 0;
	result = (char **)malloc(sizeof(char *) * (count_world(s, c) + 1));
	if (!result || !s)
		return (NULL);
	while (s[i])
	{
		if (!is_sep(s[i], c))
		{
			l = 0;
			result[k] = ft_strndup(&s[i], size_tab(&s[i], c));
			while (!is_sep(s[i], c) && s[i])
				result[k][l++] = s[i++];
			result[k++][l] = '\0';
		}
		else
			i++;
	}
	return (result[k] = NULL, result);
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

char	*ft_strndup(const char *s1, size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	while (s1[i] && i < size)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
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

// int	main(void)
// {
// 	char *str = "hello!";
// 	char **ptr;
// 	int i = 0;
// 	ptr = ft_split(str, 'k');
// 	print_tab(ptr);
// 	while (ptr[i] != NULL)
// 		free(ptr[i++]);
// 	free(ptr);
// 	return (0);
// }