/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:52:42 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/10 15:39:55 by tnolent          ###   ########.fr       */
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