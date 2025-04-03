#include "../../includes/minishell.h"

static void clear_IO_file(t_exec *exec, int IO)
{
    if (IO == 1)
    {
        close(exec->infile);
        exec->infile = open(".infile", O_RDONLY | O_WRONLY | O_TRUNC);
    }
    else if (IO == 2)
    {
        close(exec->outfile);
        exec->outfile = open(".outfile", O_RDONLY | O_WRONLY | O_TRUNC);
    }
    else
    {
        printf("No IO file given\n");
        return ;
    }
}

void display_output(t_exec *exec)
{
    char *output;

    ft_reopen_IO(exec, 2);
    output = get_file_content(exec->outfile);
    ft_putstr_fd(output, 1);
    free(output);
}

void redirect_output(t_list *list, t_exec *exec)
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
    if (list->next_list)
        ft_pipe(exec);
    else
    {
        display_output(exec);
        clear_IO_file(exec, 1);
        clear_IO_file(exec, 2);
    }
}

void ft_pipe(t_exec *exec)
{
    char *output;

    clear_IO_file(exec, 1);
    ft_reopen_IO(exec, 2);
    output = get_file_content(exec->outfile);
    ft_putstr_fd(output, exec->infile);
    clear_IO_file(exec, 2);
}
