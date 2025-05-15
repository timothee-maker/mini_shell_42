#include "minishell.h"

char **create_args(t_exec *exec)
{
	char **res;
	char *output;
    char sep;

    sep = ARG_SEP;
	close(exec->infile);
    exec->infile = open(exec->infile_path, O_RDWR | O_CREAT, 0777);
	output = get_file_content(exec->infile);
	res = ft_split(output, sep);
    if (res == NULL)
    {
        return (NULL);
    }
    close(exec->infile);
    exec->infile = open(exec->infile_path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	free(output);
	return (res);
}

void fill_args(t_list *list, t_exec *exec, t_cmd *cmd)
{
    t_element   *elem;
    char        *temp;
    char        sep;

    sep = ARG_SEP;
    ft_putstr_fd(cmd->name, exec->infile);
    write(exec->infile, &sep, 1);
    elem = list->first;
    while (elem)
    {
        temp = ft_strdup(elem->arg);
        if (!ft_strcmp(elem->token, "ARG") || !ft_strcmp(elem->token, "ENV"))
        {
            ft_putstr_fd(temp, exec->infile);
            write(exec->infile, &sep, 1);
        }
        elem = elem->next;
        free(temp);
    }
    close(exec->infile);
    exec->infile = open(exec->infile_path, O_RDWR | O_CREAT, 0777);
}

void get_infile(char *filename, t_cmd *cmd)
{
    int         fd;
    
    fd = open(filename, O_RDWR | O_TRUNC, 0777);
    if (fd == -1)
    {
        perror("Error opening infile");
        return;
    }
    cmd->input = fd;
}

void get_outfile(char *filename, t_cmd *cmd)
{
    int         fd;
    
    fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("Error opening outfile");
        return;
    }
    cmd->output = fd;
}
