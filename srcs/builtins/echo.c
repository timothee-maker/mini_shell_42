#include "../../includes/minishell.h"

void echo(t_exec *exec)
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
        printf("%s");
        if (args[i] != NULL)
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}
