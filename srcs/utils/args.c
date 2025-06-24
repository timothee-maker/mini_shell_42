/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:05:37 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/17 10:05:49 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_args_count(t_element *elem)
{
    int count;

    count = 0;
    while (elem)
    {
        if (!ft_strcmp(elem->token, "ARG") || !ft_strcmp(elem->token, "ARG-INQUOTE"))
            count++;
        elem = elem->next;
    }
    return (count + 1);
}

char	**create_args(t_element *elem, t_cmd *cmd)
{
	char	**res;
    int i;

    res = ft_malloc(sizeof(char *), get_args_count(elem) + 1, NULL);
    res[0] = ft_strdup(cmd->name);
    i = 1;
    while (elem)
    {
        if (!ft_strcmp(elem->token, "ARG") || !ft_strcmp(elem->token, "ARG-INQUOTE"))
        {
            res[i] = ft_strdup(elem->arg);
            i++;
        }
        elem = elem->next;
    }
    res[i] = NULL;
	return (res);
}

int	get_infile(char *filename, t_cmd *cmd)
{
	int	fd;

	if (cmd->input != -1)
		close(cmd->input);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening infile");
		return (2);
	}
	cmd->input = fd;
	return (0);
}

int	get_outfile(char *filename, t_cmd *cmd)
{
	static char	*last_fd = NULL;
	int			fd;

	if (cmd->output != -1 && last_fd != NULL)
		close(cmd->output);
	last_fd = filename;
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error opening outfile");
		return (2);
	}
	cmd->output = fd;
	return (0);
}

int	get_outfile_append(char *filename, t_cmd *cmd)
{
	static char	*last_fd = NULL;
	int			fd;

	if (cmd->output != -1 && last_fd != NULL)
		close(cmd->output);
	last_fd = filename;
	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error opening outfile");
		return (2);
	}
	cmd->output = fd;
	return (0);
}
