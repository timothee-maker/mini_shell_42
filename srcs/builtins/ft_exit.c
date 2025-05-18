#include "../../includes/minishell.h"

int ft_exit(t_cmd *cmd, t_exec *exec)
{
    int status;

    status = 0;
    if (cmd->args[1] != NULL)
    {
        status = ft_atoi(cmd->args[1]);
        if (status < 0)
        {
            ft_putendl_fd("exit: numeric argument required", 2);
            return (-1);
        }
        if (cmd->args[2] != NULL)
        {
            ft_putendl_fd("exit: too many arguments", 2);
            return (-1);
        }
    }
    exec->exit_status = (unsigned char) status;
    global_exit(exec);
    return (1);
}

void global_exit(t_exec *exec)
{
    int status;

    status = exec->exit_status;
    ft_free_cmd(exec->cmd);
    exec->cmd = NULL;
    unlink(exec->infile_path);
    unlink(exec->heredoc_path);
    free_env(exec->env);
    free(exec->infile_path);
    free(exec->heredoc_path);
    free(exec);
    exec = NULL;
    printf("exit\n");
    exit(status);
}
