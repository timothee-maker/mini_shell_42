#include "minishell.h"

t_exec *init_exec(char **envp)
{
	t_exec *res;

	res = malloc(sizeof(t_exec));
	res->cmd = NULL;
	res->envp = envp;
	res->env = create_env(envp);
	res->infile = open(".infile", O_RDWR | O_CREAT, 0777);
	res->outfile = open(".outfile", O_RDWR | O_CREAT, 0777);
	return (res);
}

t_cmd *init_cmd(t_list *list)
{
	t_cmd		*res;
	t_element	*elem;

	res = malloc(sizeof(t_cmd));
	res->is_builtin = 0;
	res->infiles = init_infiles(list);
	res->outfiles = init_outfiles(list);
	elem = list->first;
	while (elem)
	{
		if (!ft_strncmp(elem->token, "CMD", ft_strlen(elem->token)))
		{
			res->name = get_cmd_name(elem->arg);
			res->path = elem->arg;
		}
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
