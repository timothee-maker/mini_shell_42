#include "../../includes/minishell.h"

void pwd(t_exec *exec)
{
    t_env *var;

    var = exec->env;
    while (var)
    {
        if(!ft_strncmp(var->name, "PWD", ft_strlen(var->name)))
        {
            printf("%s\n", var->value);
            return ;
        }
        var = var->next;
    }
}
