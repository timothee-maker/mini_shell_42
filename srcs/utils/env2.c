/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:09:43 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/21 09:09:45 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_env_lenght(t_env *env)
{
	t_env	*var;
	int		i;

	var = env;
	i = 0;
	while (var)
	{
		i++;
		var = var->next;
	}
	return (i);
}

char	*fetch_value(char *name, t_exec *exec)
{
	t_env	*var;
	char	*dup_name;
	int		i;

	var = exec->env;
	i = 1;
	if (name == NULL)
		return (NULL);
	dup_name = ft_calloc(sizeof(char), ft_strlen(name));
	while (name[i] != '\0')
	{
		dup_name[i - 1] = name[i];
		i++;
	}
	while (var)
	{
		if (!ft_strcmp(var->name, dup_name))
		{
			free(dup_name);
			return (ft_strdup(var->value));
		}
		var = var->next;
	}
	free(dup_name);
	return (NULL);
}

void	replace_env(t_list *list, t_exec *exec)
{
	t_element	*elem;

	elem = list->first;
	while (elem)
	{
		if (!ft_strcmp(elem->token, "ENV")
			|| !ft_strcmp(elem->token, "ENV-INQUOTE"))
		{
			if (!ft_strcmp(elem->arg, "$"))
				elem->arg = ft_strdup("$");
			else if (!ft_strcmp(elem->arg, "$?"))
				elem->arg = ft_itoa(exec->exit_status);
			else
				elem->arg = fetch_value(elem->arg, exec);
		}
		elem = elem->next;
	}
}

char	**str_env(t_exec *exec)
{
	char	**res;
	char	*temp;
	t_env	*var;
	int		i;

	var = exec->env;
	res = malloc(sizeof(char *) * (get_env_lenght(exec->env) + 1));
	i = 0;
	while (var)
	{
		temp = NULL;
		temp = ft_strjoin(var->name, "=");
		temp = ft_custom_join(temp, var->value);
		res[i] = temp;
		i++;
		var = var->next;
	}
	res[i] = NULL;
	return (res);
}
