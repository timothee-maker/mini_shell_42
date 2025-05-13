#include "minishell.h"

char *get_first_arg(t_list *list)
{
    t_element *elem;

    elem = list->first;
    while(elem)
    {
        if (!ft_strncmp(elem->token, "ARG", ft_strlen(elem->token)))
            return (ft_strdup(elem->arg));
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
    res->heredoc_path = ft_strjoin(cwd, "/.heredoc");
	res->heredoc = open(res->heredoc_path, O_RDWR | O_CREAT, 0777);
	return (res);
}

t_cmd *init_cmd(t_list *list, t_exec *exec)
{
	t_cmd		*res;
	t_element	*elem;

	res = malloc(sizeof(t_cmd));
	res->is_builtin = 0;
    res->input = -1;
    res->output = -1;
    res->path = NULL;
    res->name = NULL;
    res->args = NULL;
    res->prev = NULL;
    res->next = NULL;
	elem = list->first;
	while (elem)
	{
		if (!ft_strncmp(elem->token, "CMD", ft_strlen(elem->token)) && elem == list->first)
		{
			res->name = get_cmd_name(elem->arg);
			res->path = find_path(res->name, exec);
		}
        else if (!ft_strncmp(elem->token, "BUILTIN", ft_strlen(elem->token)))
        {
            res->is_builtin = 1;
            res->name = ft_strdup(elem->arg);
        }
        else if (res->name == NULL)
            res->name = get_first_arg(list);
		elem = elem->next;
	}
	return (res);
}

t_cmd *assign_cmd(t_list *list, t_exec *exec)
{
    t_element *elem;
    t_cmd *res;

    res = init_cmd(list, exec);
    elem = list->first;
    while(elem)
    {
        if (!ft_strncmp(elem->token, "HERE-DOC", ft_strlen(elem->token)))
        {
            fill_heredoc(list, exec);
            res->input = open(exec->heredoc_path, O_RDWR);
            if (res->input == -1)
            {
                perror("Error opening heredoc file");
                return (NULL);
            }
        }
        else if (!ft_strncmp(elem->token, "INFILE", ft_strlen(elem->token)))
            get_infile(elem->arg, res);
        else if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
            get_outfile(elem->arg, res);
        elem = elem->next;
    }
    fill_args(list, exec, res);
    res->args = create_args(exec);
    return (res);
}

void add_command(t_exec *exec, t_cmd *cmd)
{
    t_cmd *temp;

    if (exec->cmd == NULL)
    {
        exec->cmd = cmd;
        return ;
    }
    temp = exec->cmd;
    while (temp->next)
        temp = temp->next;
    temp->next = cmd;
    cmd->prev = temp;
}
