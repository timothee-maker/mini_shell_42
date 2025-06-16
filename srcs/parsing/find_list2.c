/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:06:25 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/16 11:05:37 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_env_var(t_token *token, t_exec *exec);

int	handle_env(t_list *list, t_token *token, t_exec *exec)
{
	int	is_good;

	is_good = 0;
	if (token->split->str[0] == '$' && token->split->context != 0)
	{
		replace_env_var(token, exec);
		if (!token->split->str)
			return (1);
		is_good = find_builtin(list, token);
		if (!is_good)
		{
			is_good = find_files_redir(list, token);
			if (!is_good)
				is_good = find_cmd(list, token);
		}
	}
	if (is_good == 1)
		return (1);
	if (!is_good && token->split->context == 3)
		is_good = add_token(list, "ARG-INQUOTE", token);
	else
		is_good = add_token(list, "ARG", token);
	return (is_good);
}

static int	replace_env_var(t_token *token, t_exec *exec)
{
	char	*tmp_env;

	tmp_env = NULL;
	if (ft_strcmp(token->split->str, "$?") == 0)
	{
		tmp_env = token->split->str;
		token->split->str = ft_itoa(exec->exit_status);
		free(tmp_env);
		return (1);
	}
	tmp_env = token->split->str;
	token->split->str = fetch_value(token->split->str, exec);
	free(tmp_env);
	return (1);
}
