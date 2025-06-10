/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:31:18 by tnolent           #+#    #+#             */
/*   Updated: 2025/06/10 13:53:51 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_token(t_list *current, t_token *token, t_exec *exec);

int	parsing(char *line, t_list *list, t_exec *exec)
{
	t_split	*split;

	split = NULL;
	add_history(line);
	line = clean_line(line);
	if (!line)
		error_parsing(line, exec, split);
	split = ft_split_list_minishell(line, exec);
	if (!split)
		error_parsing(line, exec, split);
	free(line);
	line = NULL;
	if (!start_parse(split))
		return (free_split(split), -1);
	if (!analyze_line(split, list, exec))
		error_parsing(line, exec, split);
	free_split(split);
	return (1);
}

int	analyze_line(t_split *split, t_list *list, t_exec *exec)
{
	t_list	*current;
	t_token	token;
	t_split	*current_split;

	current_split = split;
	current = list;
	init_token(&token);
	while (current_split)
	{
		token.split = current_split;
		if (ft_strchr(current_split->str, '|')
			&& ft_strlen(token.split->str) == 1)
		{
			insertion_list(exec, current);
			current = current->next_list;
			current_split = current_split->next;
			init_token(&token);
			continue ;
		}
		if (!handle_token(current, &token, exec))
			return (0);
		token.position++;
		current_split = current_split->next;
	}
	return (1);
}

static int	handle_token(t_list *current, t_token *token, t_exec *exec)
{
	int	is_good;

	(void)exec;
	is_good = find_builtin(current, token);
	if (!is_good)
	{
		is_good = find_files_redir(current, token);
		if (!is_good)
		{
			is_good = find_cmd(current, token);
			if (!is_good)
				is_good = handle_env(current, token, exec);
		}
	}
	if (is_good == -1)
		return (0);
	return (1);
}
