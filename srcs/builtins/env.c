#include "../../includes/minishell.h"

void ft_env(t_exec *exec)
{
    t_env *var = exec->env;
    while(var)
    {
        printf("%s=%s\n", var->name, var->value);
        var = var->next;
    }
}
