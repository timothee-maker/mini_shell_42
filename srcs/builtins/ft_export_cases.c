#include "../../includes/minishell.h"

static int get_env_lenght(t_env *env)
{
    t_env *var;
    int i;

    var = env;
    i = 0;
    while(var)
    {
        i++;
        var = var->next;
    }
    return (i);
}

char **custom_env(t_exec *exec)
{
    char **res;
    char *name;
    char *temp;
    t_env *var;
    int i;

    var = exec->env;
    res = malloc(sizeof(char *) * (get_env_lenght(exec->env) + 1));
    i = 0;
    while(var)
    {
        temp = NULL;
        name = ft_strdup(var->name);
        if (var->value)
        {
            temp = ft_custom_join(name, "=\"");
            temp = ft_custom_join(temp, var->value);
            temp = ft_custom_join(temp, "\"");
        }
        else
            temp = ft_strdup(name);
        free(name);
        res[i] = temp;
        free(temp);
        i++;
        var = var->next;
    }
    res[i] = NULL;
    return(res);
}
