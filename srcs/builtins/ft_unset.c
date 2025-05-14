#include "../../includes/minishell.h"

int ft_unset(t_exec *exec, t_cmd *cmd)
{
    t_env *var;
    t_env *prev;
    char *var_name;
    
    var = exec->env;
    if (cmd->args[1] == NULL)
    {
        ft_putendl_fd("unset: not enough arguments", 2);
        return (2);
    }
    var_name = cmd->args[1];
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
            return (0);
        }
        prev = var;
        var = var->next;
    }
    ft_putendl_fd("unset: did not found var", 2);
    return (2);
}
