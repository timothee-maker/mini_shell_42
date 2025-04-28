#include "../../includes/minishell.h"

int is_infile(t_element *elem)
{
	if (!ft_strncmp(elem->token, "INFILE", ft_strlen(elem->token)))
		return (1);
	return (0);
}

int is_outfile(t_element *elem)
{
	if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
		return (1);
	if (!ft_strncmp(elem->token, "OUTFILE-APPEND", ft_strlen(elem->token)))
		return (1);
	return (0);
}

int get_open_mode(t_element *elem)
{
	if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
		return (O_RDWR | O_CREAT);
	if (!ft_strncmp(elem->token, "OUTFILE-APPEND", ft_strlen(elem->token)))
		return (O_RDWR | O_APPEND | O_CREAT);
	return (0);
}

char *get_file_content(int fd)
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

void ft_reopen_IO(t_exec *exec, int IO)
{
	if (IO == 1)
	{
		close(exec->infile);
		exec->infile = open(exec->infile_path, O_RDWR);
	}
	else if (IO == 2)
	{
		close(exec->outfile);
		exec->outfile = open(exec->outfile_path, O_RDWR);
	}
    else if (IO == 3)
	{
		close(exec->fstdin);
		exec->fstdin = open(exec->fstdin_path, O_RDWR);
	}
	else
	{
		printf("No IO file given\n");
		return;
	}
}
