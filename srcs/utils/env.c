/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:32 by lde-guil          #+#    #+#             */
/*   Updated: 2025/04/16 11:34:13 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(char **envp)
{
	int		i;
	t_env	*first;
    t_env   *var;
	t_env	*temp;

    temp = NULL;
	first = NULL;
	i = 0;
	while (envp[i])
	{
		var = malloc(sizeof(t_env));
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

char	*get_var_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
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
	while (*str != '=' && *str != '\0')
		str++;
	str++;
	return (no_quotes(str));
}
