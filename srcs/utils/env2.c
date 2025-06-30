/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:09:43 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/30 13:13:16 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (!var->value)
				return (free(dup_name), NULL);
			return (free(dup_name), ft_strdup(var->value));
		}
		var = var->next;
	}
	return (free(dup_name), NULL);
}

void	replace_env(t_list *list, t_exec *exec)
{
	t_element	*elem;

	elem = list->first;
	while (elem)
	{
		if (!ft_strcmp(elem->token, "ENV") || !ft_strcmp(elem->token,
				"ENV-INQUOTE"))
		{
			if (!ft_strcmp(elem->arg, "$"))
				elem->arg = ft_strdup("$");
			else if (!ft_strcmp(elem->arg, "$?"))
			{
				elem->arg = ft_itoa(exec->exit_status);
			}
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
	res = ft_malloc(sizeof(char *), (get_env_lenght(exec->env) + 1), NULL);
	i = 0;
	while (var)
	{
		if (var->name && var->value)
		{
			temp = NULL;
			temp = ft_strjoin(var->name, "=");
			temp = ft_custom_join(temp, var->value);
			res[i] = temp;
			i++;
		}
		var = var->next;
	}
	res[i] = NULL;
	return (res);
}

t_env	*mini_env(void)
{
	t_env	*env;
	t_env	*shlvl;
	t_env	*path;

	env = ft_malloc(sizeof(t_env), 1, NULL);
	env->name = ft_strdup("PWD");
	env->value = ft_strdup(getcwd(NULL, 0));
	shlvl = ft_malloc(sizeof(t_env), 1, NULL);
	shlvl->name = ft_strdup("SHLVL");
	shlvl->value = ft_itoa(1);
	env->next = shlvl;
	path = ft_malloc(sizeof(t_env), 1, NULL);
	path->name = ft_strdup("PATH");
	path->value = ft_strdup(BACKUP_PATH);
	shlvl->next = path;
	path->next = NULL;
	return (env);
}
