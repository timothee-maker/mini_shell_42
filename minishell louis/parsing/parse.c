/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:17:16 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/13 10:02:42 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		start_parse(char **split)
{
	int	i;
	int	len_split;
	
	len_split = len_tab(split);
	i = 0;
	while (split[i])
	{
		if (!syntax_error(split, len_split))
		{
			printf("Error synstax\n");
			return(0);
		}
		else if (!valid_quote(split[i]))
			return (0);
		i++;
	}
	return (1);
}

int		syntax_error(char **split, int len_split)
{
	int	i;

	if ((len_split == 1 && chr_str(split[0], ERROR_CHAR)) || ft_strchr(split[len_split - 1], '|'))
			return (0);

	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '|') && ft_strchr(split[i + 1], '|'))
			return (0);
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
