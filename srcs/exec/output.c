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
    display_output(exec);
}
