#include "minishell.h"

//static void ft_sleep(double n)
//{
//    while(n > 0)
//        n = n - 0.001;
//}

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
    int last_fd;
    if (exec->cmd->outfiles != NULL)
    {
        last_fd = get_last_outfile(exec->cmd->outfiles);
        dup2(last_fd, STDOUT_FILENO);
        close(last_fd);
    }
    else if (exec->cmd->is_pipe != 0)
	    dup2(exec->outfile, STDOUT_FILENO);
	dup2(exec->fstdin, STDIN_FILENO);
	if (execve(exec->cmd->path, exec->cmd->args, str_env(exec)) == -1)
    {
        ft_putstr_fd(exec->cmd->name, 2);
        ft_putendl_fd(": command not found", 2);
        exit(EXIT_FAILURE);
    }
}

void parent_process(pid_t pid, t_exec *exec)
{
    int status;

    status = 0;
    printf("waiting for %i ...\n", pid);
	waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        printf("%i is done\n", pid);
        redirect_output(exec);
        exec->exit_status = WEXITSTATUS(status);
    }
}
