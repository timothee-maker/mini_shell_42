#include "../../includes/minishell.h"

int ft_pwd(t_exec *exec)
{
    char	cwd[PATH_MAX];
    char    **args;

    args = create_args(exec);
    if (args[1] != NULL)
    {
        ft_putendl_fd("pwd: too many arguments", 2);
        return (2);
    }
	if (getcwd(cwd, PATH_MAX))
    {
		printf("%s\n", cwd);
        return (0);
    }
    else
    {
        ft_putendl_fd("pwd: cannot access current directory", 2);
        return (2);
    }
}
