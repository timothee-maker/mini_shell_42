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
        if (exec->cmd->is_builtin)
            return ;
		fill_args(list, exec);
		fill_heredoc(list, exec);
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
