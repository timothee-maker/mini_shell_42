#include "../../includes/minishell.h"

void add_end_env(t_env *env, t_env *var)
{
    t_env *current;

    current = env;
    while (current->next)
    {
        current = current->next;
    }
    current->next = var;
    printf("added var at the end (%s\n)", var->name);
}
