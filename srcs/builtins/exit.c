#include "../../includes/minishell.h"

void ft_exit(t_exec *exec)
{
    free_exec(exec);
    exit(EXIT_SUCCESS);
}