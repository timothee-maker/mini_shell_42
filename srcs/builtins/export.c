#include "../../includes/minishell.h"

void ft_export(t_exec *exec)
{
    t_env   *var;
    t_env   *res;
    char    *var_name;
    char    *var_value;
    char    **args;

    var = exec->env;
    res = NULL;
    args = create_args(exec);
    var_name = get_var_name(args[1]);
    var_value = get_var_value(args[1]);
    args = create_args(exec);
    while(var)
    {
        if (!ft_strncmp(var->name, var_name, ft_strlen(var_name)))
            res = var;
        var = var->next;
    }
    if (!res)
        res = malloc(sizeof(t_env));
    res->name = var_name;
    res->value = var_value;
    res->next = NULL;
    var->next = res;
    return ;
}
