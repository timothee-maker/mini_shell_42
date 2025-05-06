#include "../../includes/minishell.h"

static int is_newline(char *str)
{
    int i;
    
    i = 0;
    if (str[i] && str[i] != '-')
        return (0);
    i++;
    while(str[i] != '\0')
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void ft_echo(t_exec *exec)
{
    int newline;
    int i;
    char **args;

    args = create_args(exec);
    newline = 1;
    i = 1;
    while (args[i] && is_newline(args[i]))
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        i++;
        if (args[i] != NULL)
            printf(" ");
    }
    if (newline)
        printf("\n");
}
