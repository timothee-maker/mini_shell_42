#include "../../includes/minishell.h"

void ft_echo(t_exec *exec)
{
    int newline;
    int i;
    char **args;

    args = create_args(exec);
    newline = 1;
    i = 1;
    if (!ft_strncmp(args[i], "-n", ft_strlen(args[i])))
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], exec->outfile);
        i++;
        if (args[i] != NULL)
            ft_putstr_fd(" ", exec->outfile);;
    }
    if (newline)
        ft_putstr_fd("\n", exec->outfile);
}
