#include "../../includes/minishell.h"

t_cmd *first_cmd_init()
{
    t_cmd *res;

    res = malloc(sizeof(t_cmd));
	res->is_builtin = 0;
    res->input = -1;
    res->output = -1;
    res->pid = 0;
    res->path = NULL;
    res->name = NULL;
    res->args = NULL;
    res->prev = NULL;
    res->next = NULL;
    return (res);
}

void compare_cmd_tokens(t_cmd *res, t_element *elem, t_exec *exec, t_list *list)
{
    int first;

    first = 1;
    while (elem)
    {
        if (!ft_strncmp(elem->token, "CMD", ft_strlen(elem->token)) && first)
        {
            first = 0;
            res->name = get_cmd_name(elem->arg);
            res->path = find_path(res->name, exec);
        }
        else if (!ft_strncmp(elem->token, "BUILTIN", ft_strlen(elem->token)) && first)
        {
            first = 0;
            res->is_builtin = 1;
            res->name = ft_strdup(elem->arg);
        }
        else if (res->name == NULL && first && !ft_strcmp(elem->token, "ARG"))
        {
            first = 0;
            res->name = get_first_arg(list);
        }
        elem = elem->next;
    }
}

int assign_loop(t_element *elem, t_list *list, t_exec *exec, t_cmd *res)
{
    while(elem)
    {
        if (!ft_strncmp(elem->token, "HERE-DOC", ft_strlen(elem->token)))
        {
            fill_heredoc(list, exec);
            res->input = open(exec->heredoc_path, O_RDWR);
            if (res->input == -1)
            {
                perror("Error opening heredoc file");
                return (1);
            }
        }
        else if (!ft_strncmp(elem->token, "INFILE", ft_strlen(elem->token)))
            get_infile(elem->arg, res);
        else if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
            get_outfile(elem->arg, res);
        else if (!ft_strcmp(elem->token, "OUTFILE-APPEND"))
            get_outfile_append(elem->arg, res);
        elem = elem->next;
    }
    return (0);
}
