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

void translate_var(t_exec *exec, t_list *list)
{
    t_element *elem;
    t_env *var;
    char *varname;

    elem = list->first;
    while(elem)
    {
        var = exec->env;
        if (!ft_strncmp(elem->token, "ENV", ft_strlen(elem->token)))
        {
            while(var)
            {
                varname = get_var_name(elem->arg);
                if (!ft_strncmp(varname, var->name, ft_strlen(varname)))
                {
                    elem->arg = var->value;
                    elem->token = "ARG";
                }
                free(varname);
                var = var->next;
            }
        }
        elem = elem->next;
    }
}

char **str_env(t_exec *exec)
{
    char **res;
    char *temp;
    t_env *var;
    int i;

    var = exec->env;
    res = malloc(sizeof(char *) * get_env_lenght(exec->env));
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
    res[i] = NULL;
    return(res);
}