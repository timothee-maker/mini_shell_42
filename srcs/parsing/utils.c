/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:52:42 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/19 15:53:53 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sep_delimiter(int i, int j, char *new_line, char *line);

void	free_split(l_split *split)
{
	l_split	*current_split;
	l_split	*next;

	current_split = split;
	while (current_split)
	{
		next = current_split->next;
		free(current_split->str);
		free(current_split);
		current_split = next;
	}
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
	j = sep_delimiter(i, j, new_line, line);
	return (new_line[j] = '\0', new_line);
}

static int	sep_delimiter(int i, int j, char *new_line, char *line)
{
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
	return (j);
}

int	len_tab(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	len_list(l_split *split)
{
	int	i;

	i = 0;
	while (split)
	{
		i++;
		split = split->next;
	}
	return (i);
}
