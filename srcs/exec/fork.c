#include "../../includes/minishell.h"

static char **create_args(t_exec *exec)
{
    char **res;

    res = malloc(sizeof(char *) * 2);
    res[0] = ft_strdup(exec->cmd->name);
    res[1] = NULL;
    return (res);
}

void child_process(t_exec *exec)
{
    dup2(exec->infile, STDIN_FILENO);
    dup2(exec->outfile, STDOUT_FILENO);
    execve(exec->cmd->path, create_args(exec), exec->envp);
}

void parent_process(pid_t pid)
{

    waitpid(pid, NULL, 0);
}
