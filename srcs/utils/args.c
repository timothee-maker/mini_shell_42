/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:05:37 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/21 09:05:38 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_args(t_exec *exec)
{
	char	**res;
	char	*output;
	char	sep;

	sep = ARG_SEP;
	close(exec->infile);
	exec->infile = open(exec->infile_path, O_RDWR | O_CREAT, 0777);
	output = get_file_content(exec->infile);
	res = ft_split(output, sep);
	if (res == NULL)
	{
		return (NULL);
	}
	close(exec->infile);
	exec->infile = open(exec->infile_path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	free(output);
	return (res);
}

void	fill_args(t_list *list, t_exec *exec, t_cmd *cmd)
{
	t_element	*elem;
	char		sep;

	sep = ARG_SEP;
	ft_putstr_fd(cmd->name, exec->infile);
	write(exec->infile, &sep, 1);
	elem = list->first;
	args_loop(elem, exec, sep);
	close(exec->infile);
	exec->infile = open(exec->infile_path, O_RDWR | O_CREAT, 0777);
}

void	get_infile(char *filename, t_cmd *cmd)
{
	int	fd;

	if (cmd->input != -1)
		close(cmd->input);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening infile");
		return ;
	}
	cmd->input = fd;
}

void	get_outfile(char *filename, t_cmd *cmd)
{
	static char	*last_fd = NULL;
	int			fd;

	if (cmd->output != -1 && last_fd != NULL)
		unlink(last_fd);
	last_fd = filename;
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error opening outfile");
		return ;
	}
	cmd->output = fd;
}

void	get_outfile_append(char *filename, t_cmd *cmd)
{
	static char	*last_fd = NULL;
	int			fd;

	if (cmd->output != -1 && last_fd != NULL)
		unlink(last_fd);
	last_fd = filename;
	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error opening outfile");
		return ;
	}
	cmd->output = fd;
}
