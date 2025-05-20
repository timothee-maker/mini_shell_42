#include "../../includes/minishell.h"

void args_loop(t_element *elem, t_exec *exec, char sep)
{
    char *temp;

    while (elem)
    {
        temp = NULL;
        if (elem->arg)
            temp = ft_strdup(elem->arg);
        if (!ft_strcmp(elem->token, "ARG") || !ft_strcmp(elem->token, "ENV")
            || !ft_strcmp(elem->token, "ENV-INQUOTE"))
        {
            ft_putstr_fd(temp, exec->infile);
            if (ft_strcmp(elem->token, "ENV-INQUOTE"))
                write(exec->infile, &sep, 1);
        }
        elem = elem->next;
        if (temp)
            free(temp);
    }
}
