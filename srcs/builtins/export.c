#include "../../includes/minishell.h"

static t_env *get_var(t_exec *exec, char *name)
{
    t_env *var;
    t_env *res;
    
    var = exec->env;
    while(var)
    {
        if (!ft_strncmp(var->name, name, ft_strlen(name) + ft_strlen(var->name)))
            return (var);
        if (var->next != NULL)
            var = var->next;
        else
            break;
    }
    res = malloc(sizeof(t_env));
    res->name = NULL;
    res->value = NULL;
    res->next = NULL;
    res->exported = 1;
    var->next = res;
    return (res);
}

static void display_exported_var(t_exec *exec)
{
    t_env *var;

    var = exec->env;
    while(var)
    {
        if (var->exported == 1)
        {
            ft_putstr_fd(var->name, exec->outfile);
            ft_putstr_fd("=", exec->outfile);
            ft_putstr_fd(var->value, exec->outfile);
            ft_putstr_fd("\n", exec->outfile);
        }
        var = var->next;
    }
}

void ft_export(t_exec *exec)
{
    char    **args;
    char    *name;
    char    *value;
    t_env   *var;

    args = create_args(exec);
    if (args[1] == NULL)
        display_exported_var(exec);
    else
    {
        name = get_var_name(args[1]);
        value = get_var_value(args[1]);
        var = get_var(exec, name);
        var->name = ft_strdup(name);
        var->value = ft_strdup(value);
        free(name);
        free(value);
        free_tab(args);
    }
}
