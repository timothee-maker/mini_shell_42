#include "../../includes/minishell.h"

void display_output(t_exec *exec)
{
	char *output;

	ft_reopen_IO(exec, 2);
	output = get_file_content(exec->outfile);
	ft_putstr_fd(output, 1);
	free(output);
}

void redirect_output(t_exec *exec)
{
	t_filenode *file;
	char *output;
	int fd;

	file = exec->cmd->outfiles;
	ft_reopen_IO(exec, 2);
	output = get_file_content(exec->outfile);
	while (file)
	{
		fd = open(file->name, O_RDWR | O_CREAT, 0777);
		ft_putstr_fd(output, fd);
		file = file->next;
		close(fd);
	}
    if (exec->cmd->is_pipe != 0)
        ft_pipe(exec, output);
    else if (exec->cmd->outfiles == NULL)
        display_output(exec);
    free(output);
    clear_IO(exec, 1);
    clear_IO(exec, 2);
}

void clear_IO(t_exec *exec, int IO)
{
    if (IO == 1)
    {
        close(exec->infile);
        exec->infile = open(".infile", O_CREAT | O_RDWR | O_TRUNC, 0777);
    }
    else if (IO == 2)
    {
        close(exec->outfile);
        exec->outfile = open(".outfile", O_CREAT | O_RDWR | O_TRUNC, 0777);
    }
    else if (IO == 3)
    {
        close(exec->fstdin);
        exec->fstdin = open(".stdin", O_CREAT | O_RDWR | O_TRUNC, 0777);
    }
    else
        printf("No IO file given to clean\n");
}

void ft_pipe(t_exec *exec, char *output)
{
    clear_IO(exec, 3);
    ft_putstr_fd(output, exec->fstdin);
    ft_reopen_IO(exec, 3);
}
