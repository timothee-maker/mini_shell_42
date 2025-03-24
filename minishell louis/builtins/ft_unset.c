#include "../minishell.h"

int ft_unset(char *varname, t_data *data)
{
    t_env *prev;
    t_env *curr;

    curr = data->env[0];
    prev = NULL;
    while (curr)
    {
        if (curr->name = varname)
        {
            if (prev)
                prev->next = curr->next;
            ft_free_env_element(curr);
            return (1);
        }
        prev = curr;
        curr = curr->next;
    }
    return (0);
}