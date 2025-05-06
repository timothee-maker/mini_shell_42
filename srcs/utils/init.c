#include "minishell.h"

char *get_first_arg(t_list *list)
{
    t_element *elem;

    elem = list->first;
    while(elem)
    {
        if (!ft_strncmp(elem->token, "ARG", ft_strlen(elem->token)))
            return (elem->arg);
        elem = elem->next;
    }
    return (NULL);
}

t_exec *init_exec(char **envp)
{
	t_exec *res;
    char cwd[PATH_MAX];

    getcwd(cwd, PATH_MAX);
	res = malloc(sizeof(t_exec));
    res->exit_status = 0;
	res->cmd = NULL;
	res->env = create_env(envp);
    res->infile_path = ft_strjoin(cwd, "/.infile");
	res->infile = open(res->infile_path, O_RDWR | O_CREAT, 0777);
    res->outfile_path = ft_strjoin(cwd, "/.outfile");
	res->outfile = open(res->outfile_path, O_RDWR | O_CREAT, 0777);
    res->fstdin_path = ft_strjoin(cwd, "/.stdin");
    res->fstdin = open(res->fstdin_path, O_RDWR | O_CREAT, 0777);
    res->pids = NULL;
    res->pipe_nbr = 0;
	return (res);
}

t_cmd *init_cmd(t_list *list, t_exec *exec)
{
	t_cmd		*res;
	t_element	*elem;

	res = malloc(sizeof(t_cmd));
	res->is_builtin = 0;
    res->is_pipe = 0;
	res->infiles = init_infiles(list);
	res->outfiles = init_outfiles(list);
    res->path = NULL;
    res->name = NULL;
    res->args = NULL;
    check_pipe(list, res);
	elem = list->first;
	while (elem)
	{
		if (!ft_strncmp(elem->token, "CMD", ft_strlen(elem->token)))
		{
			res->name = get_cmd_name(elem->arg);
			res->path = find_path(res->name, exec);
		}
        else if (!ft_strncmp(elem->token, "BUILTIN", ft_strlen(elem->token)))
        {
            res->is_builtin = 1;
            res->name = elem->arg;
        }
        else if (res->name == NULL)
            res->name = get_first_arg(list);
		elem = elem->next;
	}
	return (res);
}

t_filenode *init_infiles(t_list *list)
{
	t_filenode	*res;
	t_filenode	*first;
	t_filenode	*temp;
	t_element	*elem;

	elem = list->first;
	temp = NULL;
	first = NULL;
	while (elem)
	{
		if (is_infile(elem))
		{
			res = malloc(sizeof(t_filenode));
			res->name = elem->arg;
			res->open_mode = O_RDWR;
            res->next = NULL;
			if (temp != NULL)
				temp->next = res;
			if (!first)
				first = res;
			temp = res;
		}
		elem = elem->next;
	}
	return (first);
}

t_filenode *init_outfiles(t_list *list)
{
	t_filenode *res;
	t_filenode *first;
	t_filenode *temp;
	t_element *el;

	el = list->first;
	temp = NULL;
	first = NULL;
	while (el)
	{
		if (is_outfile(el))
		{
			res = malloc(sizeof(t_filenode));
			res->name = el->arg;
			res->open_mode = get_open_mode(el);
			res->next = NULL;
			if (temp != NULL)
				temp->next = res;
			if (!first)
				first = res;
			temp = res;
		}
		el = el->next;
	}
	return (first);
}

void   *add_pid(pid_t pid, t_exec *exec)
{
    t_pid *res;
    t_pid *curr;

    curr = exec->pids;
    res = malloc(sizeof(t_pid));
    res->pid = pid;
    res->next = NULL;
    if (curr)
    {
        while(curr->next)
            curr = curr->next;
        curr->next = res;
    }
    else
        exec->pids = res;
    return (res);
}
