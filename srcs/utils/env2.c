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

void replace_env(t_list *list)
{
    t_element	*elem;

    elem = list->first;
    while(elem)
    {
        if (!ft_strncmp(elem->token, "VAR", ft_strlen(elem->token)))
        {
            elem->arg = get_var_value(elem->arg);
            elem->token = "ARG";
        }
        elem = elem->next;
    }
}

char *translate_env(t_env *var,  char *varname)
{
    while(var)
    {
        if (!ft_strncmp(var->name, varname, ft_strlen(var->name)))
            return (var->value);
        var = var->next;
    }
    return (NULL);
}

char **str_env(t_exec *exec)
{
    char **res;
    char *temp;
    t_env *var;
    int i;

    var = exec->env;
    res = malloc(get_env_lenght(exec->env));
    i = 0;
    while(var)
    {
        temp = NULL;
        temp = ft_strjoin(var->name, "=");
        temp = ft_strjoin(temp, var->value);
        res[i] = temp;
        i++;
        var = var->next;
    }
    return(res);
}