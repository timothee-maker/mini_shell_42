#include "minishell.h"

char **create_args(t_exec *exec)
{
	char **res;
	char *output;

	ft_reopen_IO(exec, 1);
	output = get_file_content(exec->infile);
	res = ft_split_minishell(output, ' ');
	free(output);
	return (res);
}

void child_process(t_exec *exec)
{
    char **env;

    env = str_env(exec);
    if (!is_stdin_empty(exec))
    {
	    dup2(exec->fstdin, STDIN_FILENO);
    }
    if (exec->cmd->is_pipe != 0 || exec->cmd->outfiles != NULL)
    {
        ft_reopen_IO(exec, 2);
	    dup2(exec->outfile, STDOUT_FILENO);
    }
	if (execve(exec->cmd->path, create_args(exec), env) == -1)
    {
        ft_putstr_fd(exec->cmd->name, 2);
        ft_putendl_fd(": command not found", 2);
    }
}

void parent_process(pid_t pid, t_exec *exec)
{
    int status;

    status = 0;
	waitpid(pid, &status, 0);
    exec->exit_status = WEXITSTATUS(status);
}
