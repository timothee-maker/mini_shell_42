/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:52:42 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/15 15:05:33 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*clean_line(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = ft_calloc((ft_strlen(line) * 3), sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_strchr(DELIMITER, line[i]))
		{
			if (j > 0 && new_line[j - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = line[i];
			if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
				new_line[j++] = line[++i];
			if (line[i + 1] && line[i + 1] != ' ')
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

int	len_tab(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	valid_quote(char *split)
{
	char 	tmp;
	int	len;

	len = ft_strlen(split) - 1;
	if (strchr(QUOTES, split[0]))
		tmp = split[0];
	else
		return (1);
	if (split[len] == tmp && len != tmp)
		return (1);
	return (0);
}

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
