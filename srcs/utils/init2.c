/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:19:02 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/27 10:35:07 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*first_cmd_init(void)
{
	t_cmd	*res;

	res = malloc(sizeof(t_cmd));
	res->is_builtin = 0;
	res->input = -1;
	res->output = -1;
	res->pid = 0;
	res->path = NULL;
	res->name = NULL;
	res->args = NULL;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

void	compare_cmd_tokens(t_cmd *res, t_element *el, t_exec *ex, t_list *list)
{
	int	first;

	first = 1;
	while (el)
	{
		if (!ft_strncmp(el->token, "CMD", ft_strlen(el->token)) && first)
		{
			first = 0;
			res->name = get_cmd_name(el->arg);
			res->path = find_path(res->name, ex);
		}
		else if (!ft_strcmp(el->token, "BUILTIN") && first)
		{
			first = 0;
			res->is_builtin = 1;
			res->name = ft_strdup(el->arg);
		}
		else if (res->name == NULL && first && !ft_strcmp(el->token, "ARG"))
		{
			first = 0;
			res->name = get_first_arg(list);
		}
		el = el->next;
	}
}

int	assign_loop(t_element *elem, t_list *list, t_exec *exec, t_cmd *res)
{
	while (elem)
	{
		if (!ft_strncmp(elem->token, "HERE-DOC", ft_strlen(elem->token)))
		{
			fill_heredoc(list, exec);
			if (g_exit_status == 130)
				return (1);
			res->input = open(exec->heredoc_path, O_RDWR);
			if (res->input == -1)
			{
				perror("Error opening heredoc file");
				return (1);
			}
		}
		else if (!ft_strncmp(elem->token, "INFILE", ft_strlen(elem->token)))
			get_infile(elem->arg, res);
		else if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
			get_outfile(elem->arg, res);
		else if (!ft_strcmp(elem->token, "OUTFILE-APPEND"))
			get_outfile_append(elem->arg, res);
		elem = elem->next;
	}
	return (0);
}
