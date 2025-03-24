/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:26:18 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/14 13:26:20 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(t_env **env)
{
	t_env	*var;
	int		i;

	i = 0;
	while (env[i])
	{
		var = env[i];
		if (var)
		{
			free(var->name);
			free(var->value);
			free(var);
		}
		i++;
	}
	free(env);
}

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i])
    {
        free(tab[i]);
        i++;
    }
}

void	display_env(t_env **env)
{
	t_env	*var;

	var = env[0];
	while (var)
	{
		ft_putstr_fd(var->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(var->value, 1);
		ft_putstr_fd("\n", 1);
		var = var->next;
	}
}

char *fetch_value(char *name, t_env **env)
{
    t_env *var;

    var = env[0];
    while (var)
    {
        if (!ft_strncmp(var->name, name, ft_strlen(var->name)))
            return (var->value);
        var = var->next;
    }
    return (NULL);
}

char *get_cmd_name(char *path)
{
    int i;
    char *res;
    char **chunks;

    chunks = ft_split(path, '/');
    res = NULL;
    i = 0;
    while(chunks[i])
    {
        if (!chunks[i+1])
            res = ft_strdup(chunks[i]);
        i++;
    }
    ft_free_tab(chunks);
    return (res);
}
