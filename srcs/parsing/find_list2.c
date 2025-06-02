/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:06:25 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/02 11:43:29 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_env(t_list *list, t_token *token, t_exec *exec)
{
	int		is_good;
	char	*tmp_env;

	is_good = 0;
	if (token->split->str[0] == '$' && token->split->context != 0)
	{
		tmp_env = token->split->str;
		token->split->str = fetch_value(token->split->str, exec);
		free(tmp_env);
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
	if (!is_good && token->split->context == 3)
		is_good = add_token(list, "ARG-INQUOTE", token);
	else
		is_good = add_token(list, "ARG", token);
	return (is_good);
}
