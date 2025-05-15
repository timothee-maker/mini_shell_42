#include "minishell.h"

void exec_line(t_exec *exec, t_list *list)
{
    t_cmd *cmd;

	while (list)
	{
        replace_env(list, exec);
        cmd = assign_cmd(list, exec);
        add_command(exec, cmd);
        list = list->next_list;
    }
    cmd = exec->cmd;
    while(cmd)
    {
        if (pipe(exec->pipe) == -1)
			return (perror("Pipe error"));
        ft_fork(exec, cmd);
        cmd = cmd->next;
    }
    cmd = exec->cmd;
    while(cmd)
    {
        wait_status(exec, cmd);
        cmd = cmd->next;
    }
    ft_free_cmd(exec->cmd);
    exec->cmd = NULL;
}

void wait_status(t_exec *exec, t_cmd *cmd)
{
    int status;
    int pid;

    status = 0;
    pid = waitpid(cmd->pid, &status, 0);
    if (pid == cmd->pid)
    {
        if (WIFEXITED(status))
            exec->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            exec->exit_status = WTERMSIG(status) + 128;
    }
    if (cmd->name == NULL)
        return ;
    if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name) + 4) && !cmd->next
        && ((cmd->args[1] != NULL && ft_atoi(cmd->args[1]) >= 0) || 
        cmd->args[1] == NULL))
        global_exit(exec);
}

int exec_cmd(t_exec *exec, t_cmd *cmd)
{
    int status;
    if (cmd->is_builtin)
    {
        status = exec_builtin(exec, cmd);
        free_exec(exec);
        return (status);
    }
    else if (cmd->path == NULL)
    {
        if (cmd->name)
        {
            printf("Command not found: %s\n", cmd->name);
            return (2);
        }
        else
            return (2);
    }
    else if (execve(cmd->path, cmd->args, str_env(exec)) == -1)
    {
        perror("Execve error");
        return (2);
    }
    return (0);
}

int exec_builtin(t_exec *ex, t_cmd *cmd)
{
    if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
        return (ft_cd(ex, cmd));
    else if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
        return (ft_echo(cmd));
    else if (!ft_strncmp(cmd->name, "env", ft_strlen(cmd->name)))
        return (ft_env(ex));
    else if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
        return (ft_exit(cmd));
    else if (!ft_strncmp(cmd->name, "export", ft_strlen(cmd->name)))
        return (ft_export(ex, cmd));
    else if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
        return (ft_pwd(cmd));
    else if (!ft_strncmp(cmd->name, "unset", ft_strlen(cmd->name)))
        return (ft_unset(ex, cmd));
    else
        return (2);
}
