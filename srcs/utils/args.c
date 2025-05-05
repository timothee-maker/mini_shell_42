#include "minishell.h"

void fill_args(t_list *list, t_exec *exec)
{
    t_element   *elem;
    t_filenode  *currfile;

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
    if (currfile)
        fill_file(currfile, exec);
}

void fill_file(t_filenode  *currfile, t_exec *exec)
{
    int         currfd;
    char        *output;

    while (currfile->next != NULL)
        currfile = currfile->next;
    currfd = open(currfile->name, currfile->open_mode);
    clear_IO(exec, 3);
    ft_reopen_IO(exec, 3);
    output = get_file_content(currfd);
    ft_reopen_IO(exec, 3);
    ft_putstr_fd(output, exec->fstdin);
    ft_reopen_IO(exec, 3);
    close(currfd);
    free(output);
}

void check_pipe(t_list *list, t_cmd *res)
{
    if (list->next_list != NULL)
        res->is_pipe = 1;
}
