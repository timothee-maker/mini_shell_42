/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:32 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/14 13:25:33 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	**create_env(char **envp)
{
	int		i;
	t_env	**res;
	t_env	*variable;

	i = 0;
	while (envp[i])
		i++;
	res = malloc((sizeof(t_env *) * i) + sizeof(NULL));
	i = 0;
	while (envp[i])
	{
		variable = malloc(sizeof(t_env));
		variable->name = get_var_name(envp[i]);
		variable->value = get_var_value(envp[i]);
		variable->next = NULL;
        res[i] = variable;
		if (i > 0)
			res[i - 1]->next = variable;
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	*no_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	if (*str == '\'' || *str == '\"')
	{
		res = malloc((ft_strlen(str) - 2 + 1) * sizeof(char));
		i = 1;
	}
	else
	{
		res = malloc((ft_strlen(str) + 1) * sizeof(char));
		i = 0;
	}
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			res[j++] = str[i++];
		}
	}
	res[j] = '\0';
	return (res);
}

static int	is_name(char c)
{
	if (c == '=')
		return (0);
	return (1);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	res[i] = '\0';
	i--;
	while (i >= 0)
	{
		res[i] = str[i];
		i--;
	}
	return (res);
}

char	*get_var_value(char *str)
{
	while (is_name(*str))
		str++;
	str++;
	return (no_quotes(str));
}
