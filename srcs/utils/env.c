/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:32 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/11 15:16:53 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(char **envp)
{
	int		i;
	t_env	*first;
	t_env	*var;
	t_env	*temp;

	temp = NULL;
	first = NULL;
	i = 0;
	while (envp[i])
	{
		var = ft_malloc(sizeof(t_env), 1, NULL);
		var->name = get_var_name(envp[i]);
		var->value = get_var_value(envp[i]);
		var->exported = 0;
		var->next = NULL;
		if (temp != NULL)
			temp->next = var;
		if (first == NULL)
			first = var;
		temp = var;
		i++;
	}
	return (first);
}

static char	*no_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	if (*str == '\'' || *str == '\"')
	{
		res = ft_malloc(sizeof(char), ft_strlen(str), NULL);
		i = 1;
	}
	else
	{
		res = ft_malloc(sizeof(char), ft_strlen(str) + 1, NULL);
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

char	*get_var_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	res = ft_malloc((i + 1) * sizeof(char), 1, NULL);
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
	while (*str != '=' && *str != '\0')
		str++;
	if (*str == '=')
		str++;
	else if (*str == '\0')
	{
		return (NULL);
	}
	return (no_quotes(str));
}
