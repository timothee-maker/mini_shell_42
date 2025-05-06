#include "../../includes/minishell.h"

void redirect_output(t_exec *exec)
{
	char *output;
    
    if (exec->pipe_nbr != 0)
    {
        ft_reopen_IO(exec, 2);
	    output = get_file_content(exec->outfile);
        exec->pipe_nbr--;
        clear_IO(exec, 3);
        ft_putstr_fd(output, exec->fstdin);
        ft_reopen_IO(exec, 3);
        free(output);
    }
    clear_IO(exec, 1);
    clear_IO(exec, 2);
}
