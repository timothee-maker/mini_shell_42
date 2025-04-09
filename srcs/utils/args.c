#include "../../includes/minishell.h"

void fill_args(t_list *list, t_exec *exec)
{
    t_element   *elem;
    t_filenode  *currfile;
    int         currfd;

    ft_putstr_fd(exec->cmd->name, exec->infile);
    ft_putstr_fd(" ", exec->infile);
    elem = list->first;
    while (elem)
    {
        if (!ft_strncmp(elem->token, "ARG", ft_strlen(elem->token)))
        {
            ft_putstr_fd(elem->arg, exec->infile);
            ft_putstr_fd(" ", exec->infile);
        }
        elem = elem->next;
    }
    currfile = exec->cmd->infiles;
    while (currfile)
    {
        currfd = open(currfile->name, currfile->open_mode);
        ft_putstr_fd(get_file_content(currfd), exec->infile);
        ft_putstr_fd(" ", exec->infile);
        close(currfd);
        currfile = currfile->next;
    }
}
