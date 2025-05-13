#include "minishell.h"

void ft_fork(t_exec *exec, t_cmd *cmd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("Fork error");
        return ;
    }
    if (pid > 0)
    {
        cmd->pid = pid;
        parent_process(cmd, exec->pipe);
    }
    else
        child_process(cmd, exec->pipe, exec);
    return ;
}

void child_process(t_cmd *cmd, int pipe[2], t_exec *exec)
{
    int status;

    status = 0;
    close(pipe[0]);
    if (cmd->input >= 0)
    {
        dup2(cmd->input, STDIN_FILENO);
        close(cmd->input);
    }
    if (cmd->output >= 0)
    {
        dup2(cmd->output, STDOUT_FILENO);
        close(cmd->output);
    }
    else if (cmd->next != NULL)
        dup2(pipe[1], STDOUT_FILENO);
    close(pipe[1]);
    status = exec_cmd(exec, cmd);
    exit(status);
}

void parent_process(t_cmd *cmd, int pipe[2])
{
    close(pipe[1]);
    if (cmd->input >= 0)
        close(cmd->input);
    if (cmd->input == -1)
		cmd->input = pipe[0];
    if (cmd->next != NULL && cmd->next->input == -1)
        cmd->next->input = pipe[0];
}
