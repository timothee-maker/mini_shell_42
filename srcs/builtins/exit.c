#include "../../includes/minishell.h"

int ft_exit(t_exec *exec)
{
    char **args;
    int status;

    status = 0;
    args = create_args(exec);
    if (args[1] != NULL)
    {
        status = ft_atoi(args[1]);
        if (status < 0)
        {
            ft_putendl_fd("exit: numeric argument required", 2);
            return (2);
        }
        if (args[2] != NULL)
        {
            ft_putendl_fd("exit: too many arguments", 2);
            return (2);
        }
    }
    free_exec(exec);
    exit((unsigned char) status);
}
