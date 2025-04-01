#include "../../includes/minishell.h"

void exec_line(t_exec *exec, t_list *list)
{
    while (list)
    {
        exec->cmd = init_cmd(list);
        exec_cmd(exec);
        ft_reopen_IO(exec, 2);
        display_output(exec);
        //free_cmd(exec->cmd);
        list = list->next_list;
    }
}

void exec_cmd(t_exec *exec)
{
    pid_t pid;

    pid = fork();
    if (pid)
        parent_process(pid);
    else
        child_process(exec);
}
