#include "../minishell.h"

int ft_export(char *var, t_data *data)
{
    t_env *env;
    t_env *element;

    element = data->env[0];
    env = malloc(sizeof(t_env));
    if (!env)
        return (0);
    env->name = get_var_name(var);
    env->value = get_var_value(var);
    while (element->next)
    {
        element = element->next;
    }
    element->next = env;
    return (1);
}