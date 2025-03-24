#include "../minishell.h"

static int get_args_num(t_list *list)
{
    t_element *elem;
    int res;

    elem = list->first;
    res = 0;
    while(elem)
    {
        if (!ft_strncmp(elem->token, "ARG", ft_strlen(elem->token)))
            res++;
        elem = elem->next;
    }
    return (res);
}

t_data *init_data(char **envp)
{
    t_data *data;

    data = malloc(sizeof(data));
    data->env = create_env(envp);
    data->envp = envp;
    data->list = initialisation();
    return (data);
}

t_cmd *create_cmd(t_list *list)
{
    t_cmd *cmd;
    t_element *elem;
    int i;
    
    cmd = malloc(sizeof(t_cmd));
    cmd->args = malloc(sizeof(char *) * (get_args_num(list) + 1) + sizeof(NULL));
    elem = list->first;
    i = 0;
    while(elem)
    {
        if (!ft_strncmp(elem->token, "ARG", ft_strlen(elem->token)))
            cmd->args[i++] = elem->arg;
        else if (!ft_strncmp(elem->token, "CMD", ft_strlen(elem->token)))
        {
            cmd->name = get_cmd_name(elem->arg);
            cmd->path = elem->arg;
            cmd->args[i++] = cmd->name;
        }
        else if (!ft_strncmp(elem->token, "INFILE", ft_strlen(elem->token)))
            cmd->infile = elem->arg;
        else if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
            cmd->outfile = elem->arg;
        elem = elem->next;
    }
    cmd->args[i] = NULL;
    return (cmd);
}

t_cmd *create_builtin(t_list *list)
{
    t_cmd *cmd;
    t_element *elem;
    int i;
    
    cmd = malloc(sizeof(t_cmd));
    cmd->args = malloc(sizeof(char *) * (get_args_num(list) + 1) + sizeof(NULL));
    elem = list->first;
    i = 0;
    while(elem)
    {
        if (!ft_strncmp(elem->token, "ARG", ft_strlen(elem->token)))
            cmd->args[i++] = elem->arg;
        else if (!ft_strncmp(elem->token, "BUILTIN", ft_strlen(elem->token)))
        {
            cmd->name = elem->arg;
            cmd->builtin = 1;
        }
        else if (!ft_strncmp(elem->token, "INFILE", ft_strlen(elem->token)))
            cmd->infile = elem->arg;
        else if (!ft_strncmp(elem->token, "OUTFILE", ft_strlen(elem->token)))
            cmd->outfile = elem->arg;
        elem = elem->next;
    }
    cmd->args[i] = NULL;
    return (cmd);
}
