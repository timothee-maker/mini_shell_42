#include "../../includes/minishell.h"

void display_output(t_exec *exec)
{
    char *output;

    output = get_file_content(exec->outfile);
    ft_putstr_fd(output, 1);
    free(output);
}
