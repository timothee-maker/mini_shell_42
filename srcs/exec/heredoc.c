#include "../../includes/minishell.h"

static void read_hdoc(t_exec *exec, char *delimit)
{
    char *input;

    input = NULL;
    clear_IO(exec, 3);
    input = readline("> ");
    if (ft_strncmp(input, delimit, ft_strlen(input)))
        ft_putendl_fd(input, exec->fstdin);
    while (ft_strncmp(input, delimit, ft_strlen(input)))
    {
        input = readline("> ");
        if (ft_strncmp(input, delimit, ft_strlen(input)))
            ft_putendl_fd(input, exec->fstdin);
    }
    ft_reopen_IO(exec, 3);
}

void fill_heredoc(t_list *list, t_exec *exec)
{
    t_element *elem;

    elem = list->first;
    while (elem)
    {
        if (!ft_strncmp(elem->token, "HERE-DOC", ft_strlen(elem->token)))
        {
            elem = elem->next;
            if (!ft_strncmp(elem->token, "DELIMITER", ft_strlen(elem->token)))
                read_hdoc(exec, elem->arg);
        }
        elem = elem->next;
    }
}
