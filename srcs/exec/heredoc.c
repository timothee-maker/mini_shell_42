#include "../../includes/minishell.h"

static void read_hdoc(t_exec *exec, char *delimit)
{
    char *input;

    input = NULL;
    clear_IO(exec, 3);
    while (ft_strncmp(input, delimit, ft_strlen(input)))
    {
        input = readline("heredoc> ");
        if (ft_strncmp(input, delimit, ft_strlen(input)))
            ft_putendl_fd(input, exec->fstdin);
    }
}

void fill_heredoc(t_list *list, t_exec *exec)
{
    t_element *elem;

    elem = list->first;
    while (elem)
    {
        if (!ft_strncmp(elem->token, "HEREDOC", ft_strlen(elem->token)))
        {
            elem = elem->next;
            if (!ft_strncmp(elem->token, "DELIMIT", ft_strlen(elem->token)))
                read_hdoc(exec, elem->arg);
        }
        elem = elem->next;
    }
}
