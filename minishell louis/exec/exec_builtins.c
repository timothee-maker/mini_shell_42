#include "../minishell.h"

void exec_builtin(t_data *data) // a faire : env export pwd unset
{
    char *name;
    
    name = data->cmd->name;
    if (!ft_strncmp(name, "cd", ft_strlen(name)))
        data->exit_status = ft_cd(data->cmd->args[0]);
    if (!ft_strncmp(name, "echo", ft_strlen(name)))
        data->exit_status = ft_echo(data->cmd->args);
}