/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:12:01 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/21 09:12:03 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_infile(t_element *elem)
{
	if (!ft_strncmp(elem->token, "INFILE", ft_strlen(elem->token)))
		return (1);
	return (0);
}

int	is_outfile(t_element *elem)
{
	if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
		return (1);
	if (!ft_strncmp(elem->token, "OUTFILE-APPEND", ft_strlen(elem->token)))
		return (1);
	return (0);
}

char	*get_file_content(int fd)
{
	char	*res;
	char	*str;
	int		bytes;
	int		fd2;

	fd2 = dup(fd);
	res = ft_calloc(1, 1);
	bytes = 1;
	while (bytes > 0)
	{
		str = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		bytes = read(fd2, str, BUFFER_SIZE);
		res = ft_custom_join(res, str);
		free(str);
	}
	close(fd2);
	return (res);
}

void reopen_IO(t_exec *exec)
{
    close(exec->infile);
    close(exec->heredoc);
    exec->infile = open(exec->infile_path, O_RDWR | O_CREAT, 0777);
    exec->heredoc = open(exec->heredoc_path, O_RDWR | O_CREAT, 0777);
}