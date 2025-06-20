/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:31:59 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/12 11:45:41 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_parsing(char *line, t_exec *exec, t_split *split)
{
	if (line)
		free(line);
	if (split)
		free_split(split);
	if (exec)
		free_exec(exec);
	printf("AYYYYYYY le malloc a pete");
	exit(0);
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

int	is_in_quotes(int position, char *str)
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

int	valid_quote(char *split)
{
	char	tmp;
	int		len;

	len = ft_strlen(split) - 1;
	if (strchr(QUOTES, split[0]))
		tmp = split[0];
	else
		return (1);
	if (split[len] == tmp && len != tmp)
		return (1);
	return (0);
}

char	*extract_var_name(const char *s, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i + 1;
	len = 0;
	while (s[start + len] && !ft_strchr(NO_ENV, s[start + len]) && s[start
			+ len] != '$')
		len++;
	if (s[start] == '?')
		len = 1;
	if (len == 0)
		return (NULL);
	var_name = ft_malloc(sizeof(char) * (len + 2), 1, NULL);
	if (!var_name)
		return (NULL);
	var_name[0] = '$';
	ft_strncpy(var_name + 1, s + *i + 1, len);
	var_name[len + 1] = '\0';
	*i += len + 1;
	return (var_name);
}
