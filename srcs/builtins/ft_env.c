#include "../../includes/minishell.h"

int ft_env(t_exec *exec)
{
    t_env *var = exec->env;
    while(var != NULL)
    {
        if (var->name != NULL && var->value != NULL)
        printf("%s=%s\n", var->name, var->value);
        var = var->next;
    }
    return (0);
}
