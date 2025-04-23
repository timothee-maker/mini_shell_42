#include "../../includes/minishell.h"

void ft_env(t_exec *exec)
{
    t_env *var = exec->env;
    while(var)
    {
        ft_putstr_fd(var->name, exec->outfile);
        ft_putstr_fd("=", exec->outfile);
        ft_putstr_fd(var->value, exec->outfile);
        ft_putstr_fd("\n", exec->outfile);
        var = var->next;
    }
}
