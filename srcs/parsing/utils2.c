/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:43:31 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/06 11:43:57 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char		*new_str;
	size_t		i;
	int			j;

	j = 0;
	i = 0;
	if (!ft_strchr2(QUOTES, str))
		return (ft_strdup(str));
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	if (!new_str)
		return (NULL);
	while(i < ft_strlen(str))
	{
		if (!ft_strchr(QUOTES, str[i]))
			new_str[j++] = str[i++];
		else
			i++;
	}
	return (new_str);
}

char	*remove_quotes_around(char *str)
{
	char		*new_str;
	char 		tmp_quote;
	size_t		i;
	int			j;

	j = 0;
	i = 0;
	tmp_quote = 0;
	if (!ft_strchr2(QUOTES, str))
		return (ft_strdup(str));
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str || !str)
		return (NULL);
	while (str[i])
	{
		if (ft_strchr(QUOTES, str[i]))
			tmp_quote = str[i++];
		while (str[i])
		{
			if (str[i] == tmp_quote)
				break;
			if (ft_strchr(QUOTES, str[i]) && (tmp_quote == 0))
				tmp_quote = str[i++];
			if (str[i] == tmp_quote)
				break;
			if (!str[i])
				break;
			new_str[j++] = str[i++];
		}
		if (!str[i])
			break;
		i++;
		tmp_quote = 0;
	}
	return (new_str[j] = '\0', new_str);
}

int	ft_strchr2(char *str1, char *str2)
{
	int i;
	int	j;
	
	i = 0;
	j = 0;
	while (str1[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str1[i] == str2[j++])
				return (1);
		}
		i++;
	}
	return (0);
}

void	empty_string_case(char *split, t_list *list, int index)
{
	if (ft_strlen(split) == 0)
		return ;
	add_token(list, remove_quotes_around(split), "ARG", index);
}

int	check_valid_dollar(char *split)
{
	int		i;
	char	tmp;

	tmp = 0;
	i = 0;
	if (split[0] == '$')
		return (1);
	while (split[i])
	{
		if (tmp == split[i])
			tmp = 0;	
		if (ft_strchr(QUOTES, split[i]))
			tmp = split[i];
		if (split[i] == '$' && (tmp == '\"' || tmp == 0))
			return (1);
		i++;
	}
	return (0);
}
