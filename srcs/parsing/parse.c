/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:17:16 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/12 14:49:06 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_in_quotes(int position, char *str);

int		start_parse(char **split)
{
	int	i;
	int	len_split;
	
	len_split = len_tab(split);
	i = 0;
	while (split[i])
	{
		if (!syntax_error(split[i], len_split, i + 1))
			return(0);
		i++;
	}
	return (1);
}

int		syntax_error(char *split, int len_split, int position)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (len_split == position && ft_strchr(DELIMITER, split[i]) && !is_in_quotes(i, split))
		{
			printf("minishell : parse error near '%c'\n", split[i]);
			return (0);
		}
		if (position == 1 && ft_strchr(DELIMITER2, split[i]) && !is_in_quotes(i, split))
		{
			printf("minishell : parse error near '%c'\n", split[i]);
			return (0);
		}
		i++;
	}
	
	return (1);
}

int	parse_one_case(char *split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strchr(ERROR_CHAR, split[i]))
		{
			printf("Invalid syntax error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

char	*chr_str(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j])
		{
			if (str[i] == to_find[j++])
				return (str);
		}
		i++;
	}
	return (NULL);
}

int		is_in_quotes(int position, char *str)
{
	int		i;
	char	tmp;

	i = 0;
	tmp = 0;
	if (!str[position])
		return (0);
	while (str[i])
	{
		if (tmp == 0 && ft_strchr(QUOTES, str[i]))
			tmp = str[i];
		else if (ft_strchr(QUOTES, str[i]) && tmp)
			tmp = 0;
		if (i == position && tmp != 0)
			return (1);
		i++;
	}
	return (0);
}
