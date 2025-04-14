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
		fd = open(file->name, file->open_mode);
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

void ft_pipe(t_exec *exec, char *output)
{
    clear_IO(exec, 3);
    ft_putstr_fd(output, exec->fstdin);
    ft_reopen_IO(exec, 3);
}
