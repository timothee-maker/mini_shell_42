/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:22:37 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/10 16:05:02 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_first_arg(t_list *list)
{
	t_element	*elem;

	elem = list->first;
	while (elem)
	{
		if (!ft_strncmp(elem->token, "ARG", ft_strlen(elem->token)))
        {
            if (access(elem->arg, F_OK) == 0 && access(elem->arg, X_OK) != 0)
            {
                ft_putstr_fd("Permission denied: ", 2);
                return (NULL);
            }
			return (ft_strdup(elem->arg));
        }
		elem = elem->next;
	}
	return (NULL);
}

t_exec	*init_exec(char **envp)
{
	t_exec	*res;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	res = malloc(sizeof(t_exec));
	res->exit_status = 0;
	res->cmd = NULL;
	res->temp_cmd = NULL;
	if (envp[0] == NULL)
		res->env = mini_env();
	else
		res->env = create_env(envp);
	res->infile_path = ft_strjoin(cwd, "/.infile");
	res->infile = open(res->infile_path, O_RDWR | O_CREAT, 0777);
	res->heredoc_path = ft_strjoin(cwd, "/.heredoc");
	res->heredoc = open(res->heredoc_path, O_RDWR | O_CREAT, 0777);
	res->liste = NULL;
	return (res);
}

t_cmd	*init_cmd(t_list *list, t_exec *exec)
{
	t_cmd		*res;
	t_element	*elem;

	res = first_cmd_init();
	elem = list->first;
	compare_cmd_tokens(res, elem, exec, list);
	return (res);
}

t_cmd	*assign_cmd(t_list *list, t_exec *exec)
{
	t_element	*elem;
	t_cmd		*res;

	res = init_cmd(list, exec);
	exec->temp_cmd = res;
	elem = list->first;
	if (assign_loop(elem, list, exec, res))
    {
        res->to_exec = 0;
        exec->exit_status = 1;
    }
	fill_args(list, exec, res);
	res->args = create_args(exec);
	exec->temp_cmd = NULL;
	return (res);
}

void	add_command(t_exec *exec, t_cmd *cmd)
{
	t_cmd	*temp;

	if (exec->cmd == NULL)
	{
		exec->cmd = cmd;
		return ;
	}
	temp = exec->cmd;
	while (temp->next)
		temp = temp->next;
	temp->next = cmd;
	cmd->prev = temp;
}
