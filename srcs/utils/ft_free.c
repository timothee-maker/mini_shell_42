#include "../../includes/minishell.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_env(t_env *env)
{
	t_env *var;
    t_env *next;

    var = env;
    next = NULL;
	while (var)
	{
		free(var->name);
        free(var->value);
        next = var->next;
        free(var);
        var = next;
	}
}

void ft_free_cmd(t_cmd *cmd)
{
    t_cmd *next;

    while(cmd)
    {
        if (cmd->name)
            free(cmd->name);
        if (cmd->path)
            free(cmd->path);
        free_tab(cmd->args);
        if (cmd->input >= 0)
            close(cmd->input);
        if (cmd->output >= 0)
            close(cmd->output);
        next = cmd->next;
        free(cmd);
        cmd = NULL;
        cmd = next;
    }
}

void free_exec(t_exec *exec)
{
    ft_free_cmd(exec->cmd);
    exec->cmd = NULL;
    free_env(exec->env);
    free(exec->infile_path);
    free(exec->heredoc_path);
    free(exec);
    exec = NULL;
}
