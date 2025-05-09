#include "minishell.h"

void exec_line(t_exec *exec, t_list *list)
{
    t_pid *curr_pid;

	while (list)
	{
		exec->cmd = init_cmd(list, exec);
        replace_env(list, exec);
        fill_heredoc(list, exec);
		fill_args(list, exec);
        exec->cmd->args = create_args(exec);
        exec->pipe_nbr += exec->cmd->is_pipe;
        if (exec->cmd->is_builtin == 1)
		    exec_builtin(exec);
        else
        {
            exec_cmd(exec);
        }
        clear_IO(exec, 1);
		list = list->next_list;
	}
    curr_pid = exec->pids;
    while(curr_pid)
    {
        parent_process(curr_pid->pid, exec);
        curr_pid = curr_pid->next;
    }
    clear_IO(exec, 1);
    clear_IO(exec, 2);
    clear_IO(exec, 3);
}

void exec_cmd(t_exec *exec)
{
	pid_t pid;

	pid = fork();
	if (pid)
        add_pid(pid, exec);
	else
    {
		child_process(exec);
    }
}

void exec_builtin(t_exec *ex)
{
    if (!ft_strncmp(ex->cmd->name, "cd", ft_strlen(ex->cmd->name)))
        ft_cd(ex);
    else if (!ft_strncmp(ex->cmd->name, "echo", ft_strlen(ex->cmd->name)))
        return (ft_echo(ex));
    else if (!ft_strncmp(ex->cmd->name, "env", ft_strlen(ex->cmd->name)))
        return (ft_env(ex));
    else if (!ft_strncmp(ex->cmd->name, "exit", ft_strlen(ex->cmd->name)))
        ft_exit(ex);
    else if (!ft_strncmp(ex->cmd->name, "export", ft_strlen(ex->cmd->name)))
        return (ft_export(ex));
    else if (!ft_strncmp(ex->cmd->name, "pwd", ft_strlen(ex->cmd->name)))
        ft_pwd(ex);
    else if (!ft_strncmp(ex->cmd->name, "unset", ft_strlen(ex->cmd->name)))
        return (ft_unset(ex));
    else
        return ;
}
