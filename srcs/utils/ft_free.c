/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:16:53 by lde-guil          #+#    #+#             */
/*   Updated: 2025/07/23 14:50:50 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_env(t_env *env)
{
	t_env	*var;
	t_env	*next;

	var = env;
	next = NULL;
	while (var)
	{
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		next = var->next;
		free(var);
		var = next;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		if (cmd->name)
			free(cmd->name);
		if (cmd->path)
			free(cmd->path);
		if (cmd->args)
			free_tab(cmd->args);
		if (cmd->input >= 0)
			close(cmd->input);
		if (cmd->output >= 0)
			close(cmd->output);
		if (cmd->heredoc_content)
			free(cmd->heredoc_content);
		next = cmd->next;
		free(cmd);
		cmd = NULL;
		cmd = next;
	}
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->cmd)
		ft_free_cmd(exec->cmd);
	if (exec->temp_cmd)
		ft_free_cmd(exec->temp_cmd);
	exec->cmd = NULL;
	if (exec->heredoc_path)
		free(exec->heredoc_path);
	if (exec->infile_path)
		free(exec->infile_path);
	if (exec->env)
		free_env(exec->env);
	if (exec->heredoc != -1)
		close(exec->heredoc);
	if (exec->infile != -1)
		close(exec->infile);
	if (exec->liste)
		free_list(exec, exec->liste);
	free(exec);
}
