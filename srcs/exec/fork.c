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
	    dup2(exec->fstdin, STDIN_FILENO);
    if (exec->cmd->is_pipe != 0 || exec->cmd->outfiles != NULL)
	    dup2(exec->outfile, STDOUT_FILENO);
	execve(exec->cmd->path, create_args(exec), env);
}

void parent_process(pid_t pid)
{
    int status;

    status = 0;
	waitpid(pid, &status, 0);
}
