#include "../../includes/minishell.h"

void ft_unset(t_exec *exec)
{
    t_env *var;
    t_env *prev;
    char *var_name;
    char **args;
    
    var = exec->env;
    args = create_args(exec);
    if (args[1] == NULL)
    {
        ft_putendl_fd("unset: not enough arguments", 2);
        return ;
    }
    var_name = args[1];
    prev = NULL;
    while(var)
    {
        if (!ft_strncmp(var->name, var_name, ft_strlen(var_name)))
        {
            free(var->name);
            free(var->value);
            if (prev != NULL)
                prev->next = var->next;
            free(var);
            return ;
        }
        prev = var;
        var = var->next;
    }
}
