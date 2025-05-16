#include "../../includes/minishell.h"

static int check_input(char *input, char *delimit)
{
    if (input[0] == '\0')
        return (1);
    if (ft_strcmp(input, delimit))
        return (1);
    return (0);
}

static void read_hdoc(t_exec *exec, char *delimit)
{
    char *input;

    input = NULL;
    close(exec->heredoc);
    exec->heredoc = open(exec->heredoc_path, O_RDWR | O_TRUNC, 0777);
    if (exec->heredoc == -1)
    {
        perror("Error opening heredoc file");
        return;
    }
    input = readline("> ");
    if (check_input(input, delimit))
        ft_putendl_fd(input, exec->heredoc);
    while (check_input(input, delimit))
    {
        input = readline("> ");
        if (ft_strncmp(input, delimit, ft_strlen(input)))
            ft_putendl_fd(input, exec->heredoc);
    }
    close(exec->heredoc);
    exec->heredoc = open(exec->heredoc_path, O_RDWR);
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
