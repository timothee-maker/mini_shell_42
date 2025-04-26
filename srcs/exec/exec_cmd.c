#include "minishell.h"

void exec_line(t_exec *exec, t_list *list)
{
	while (list)
	{
		exec->cmd = init_cmd(list);
        if (!exec->cmd->name && exec->cmd->is_builtin == 0)
        {
            ft_putstr_fd("command not found: ", 2);
            ft_putendl_fd(list->first->arg, 2);
            return ;
        }
        replace_env(list, exec);
		fill_args(list, exec);
		fill_heredoc(list, exec);
        if (exec->cmd->is_builtin == 1)
		    exec_builtin(exec);
        else
            exec_cmd(exec);
		redirect_output(exec);
		free_cmd(exec->cmd);
		list = list->next_list;
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
		parent_process(pid);
	else
    {
		child_process(exec);
    }
}

void exec_builtin(t_exec *ex)
{
    if (!ft_strncmp(ex->cmd->name, "cd", ft_strlen(ex->cmd->name)))
        return (ft_cd(ex));
    else if (!ft_strncmp(ex->cmd->name, "echo", ft_strlen(ex->cmd->name)))
        return (ft_echo(ex));
    else if (!ft_strncmp(ex->cmd->name, "env", ft_strlen(ex->cmd->name)))
        return (ft_env(ex));
    else if (!ft_strncmp(ex->cmd->name, "exit", ft_strlen(ex->cmd->name)))
        return (ft_exit(ex));
    else if (!ft_strncmp(ex->cmd->name, "export", ft_strlen(ex->cmd->name)))
        return (ft_export(ex));
    else if (!ft_strncmp(ex->cmd->name, "pwd", ft_strlen(ex->cmd->name)))
        return (ft_pwd(ex));
    else if (!ft_strncmp(ex->cmd->name, "unset", ft_strlen(ex->cmd->name)))
        return (ft_unset(ex));
    else
        return ;
}
