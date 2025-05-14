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

char *fetch_value(char *name, t_exec *exec)
{
    t_env *var;
    char *dup_name;
    int i;

    var = exec->env;
    i = 1;
    if (name == NULL)
        return (NULL);
    dup_name = ft_calloc(sizeof(char), ft_strlen(name));
    while(name[i] != '\0')
    {
        dup_name[i - 1] = name[i];
        i++;
    }
    while(var)
    {
        if (!ft_strncmp(var->name, dup_name, ft_strlen(var->name) + ft_strlen(dup_name)))
        {
            free(dup_name);
            return (ft_strdup(var->value));
        }
        var = var->next;
    }
    free(dup_name);
    return (NULL);
}

void replace_env(t_list *list, t_exec *exec)
{
    t_element *elem;

    elem = list->first;
    while (elem)
    {
        if (!ft_strncmp(elem->token, "ENV", ft_strlen(elem->token)))
        {
            if (!ft_strncmp(elem->arg, "$", ft_strlen(elem->arg) + ft_strlen("$")))
            {
                elem->token = "ARG";
                elem->arg = ft_strdup("$");
            }
            else if (!ft_strncmp(elem->arg, "$?", ft_strlen(elem->arg) + ft_strlen("$?")))
                elem->arg = ft_itoa(exec->exit_status);
            else
                elem->arg = fetch_value(elem->arg, exec);
            elem->token = "ARG";
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
    res = malloc(sizeof(char *) * (get_env_lenght(exec->env) + 1));
    i = 0;
    while(var)
    {
        temp = NULL;
        temp = ft_strjoin(var->name, "=\"");
        temp = ft_strjoin(temp, var->value);
        temp = ft_strjoin(temp, "\"");
        res[i] = temp;
        i++;
        var = var->next;
    }
    res[i] = NULL;
    return(res);
}