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

int ft_echo(t_cmd *cmd)
{
    int newline;
    int i;

    newline = 1;
    i = 1;
    while (cmd->args[i] && is_newline(cmd->args[i]))
    {
        newline = 0;
        i++;
    }
    while (cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        i++;
        if (cmd->args[i] != NULL)
            printf(" ");
    }
    if (newline)
        printf("\n");
    return (0);
}
