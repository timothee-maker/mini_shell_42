#include "../../includes/minishell.h"

void ft_pwd(t_exec *exec)
{
    t_env *var;

    var = exec->env;
    while (var)
    {
        if(!ft_strncmp(var->name, "PWD", ft_strlen(var->name)))
        {
            ft_putendl_fd(var->value, exec->outfile);
            return ;
        }
        var = var->next;
    }
}
