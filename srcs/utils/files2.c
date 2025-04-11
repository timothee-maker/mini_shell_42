#include "../../includes/minishell.h"

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

int is_stdin_empty(t_exec *exec)
{
    int bytes;

    bytes = read(exec->fstdin, NULL, 1);
    ft_reopen_IO(exec, 3);
    if (bytes)
        return (0);
    return (1);
}
