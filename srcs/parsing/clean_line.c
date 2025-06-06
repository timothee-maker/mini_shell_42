/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:48:17 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/06 12:49:36 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sep_delimiter(int i, int j, char *new_line, char *line);

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

static int	handle_delimiter(int i, int j, char *new_line, char *line,
		int in_quote)
{
	if (!in_quote)
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
	{
		new_line[j++] = line[i];
		if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
			new_line[j++] = line[++i];
	}
	return (j);
}

static void	update_quote_state(char c, int *in_quote, char *quote)
{
	if ((c == '\'' || c == '\"'))
	{
		if (!(*in_quote))
		{
			*in_quote = 1;
			*quote = c;
		}
		else if (*quote == c)
		{
			*in_quote = 0;
			*quote = 0;
		}
	}
}

static int	sep_delimiter(int i, int j, char *new_line, char *line)
{
	int		in_quote;
	char	quote;

	in_quote = 0;
	quote = 0;
	while (line[i])
	{
		update_quote_state(line[i], &in_quote, &quote);
		if ((line[i] == '\'' || line[i] == '\"'))
		{
			new_line[j++] = line[i++];
			continue ;
		}
		if (ft_strchr(DELIMITER, line[i]))
			j = handle_delimiter(i, j, new_line, line, in_quote);
		else
			new_line[j++] = line[i];
		i++;
	}
	return (j);
}
