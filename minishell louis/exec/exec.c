#include "../minishell.h"

void exec_list(t_data *data)
{
    t_list *list;

    list = data->list;
    while(list)
    {
        if (is_builtin(list))
            is_builtin(list);
        else
            data->cmd = create_cmd(list);
        exec(data);
        ft_free_cmd(data->cmd);
        list = list->next_list;
    }
}

void exec(t_data *data)
{
    if (data->cmd->builtin)
        exec_buitin(data);
    else
        exec_command(data);
}

void exec_command(t_data *data)
{
    t_cmd *cmd;
    pid_t pid;

    pid = fork();
    cmd = data->cmd;
    if (pid)
    {
        waitpid(pid, NULL, 0);
    }
    else if (!pid)
        child_pr(data);
}

void child_pr(t_data *data)
{
    if (execve(data->cmd->path, data->cmd->args, data->envp) == -1)
    {
       printf("%s : command not found\n", data->cmd->path);
       return ;
    }
}
