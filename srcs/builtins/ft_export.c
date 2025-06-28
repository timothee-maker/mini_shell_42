/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:04 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/19 11:16:52 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_tab(char **tab, int len)
{
	int		i;
	int		j;
	int		diff;
	char	*temp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(tab[i], tab[j], INT_MAX);
			if (diff > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
				continue ;
			}
			j++;
		}
		i++;
	}
}

static int	no_args(t_exec *exec)
{
	char	**tab;
	int		i;

	i = 0;
	tab = str_env(exec);
	sort_tab(tab, len_tab(tab));
	while (tab[i])
		printf("export %s\n", tab[i++]);
	free_tab(tab);
	return (0);
}

int	ft_export(t_exec *exec, t_cmd *cmd)
{
	if (cmd->args[1] == NULL)
		return (exec->exit_status = 0, no_args(exec));
	else
		return (exec->exit_status = 0, export_next(cmd, exec));
}

void	put_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}
