#include "../minishell.h"

void ft_free_env_element(t_env *var)
{
    free(var->name);
	free(var->value);
	free(var);
}

void ft_free_cmd(t_cmd *cmd)
{
    int i;

    i = 0;
    free(cmd->name);
    free(cmd->path);
    if (cmd->infile)
        free(cmd->infile);
    if (cmd->outfile)
        free(cmd->outfile);
}