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

void free_filenode(t_filenode *fnode)
{
	t_filenode *temp;

	while (fnode != NULL)
	{
		free(fnode->name);
		temp = fnode->next;
		free(fnode);
		fnode = temp;
	}
}

void free_cmd(t_cmd *cmd)
{
	free(cmd->name);
    if (cmd->path != NULL)
	    free(cmd->path);
	free_filenode(cmd->infiles);
	free_filenode(cmd->outfiles);
    free_tab(cmd->args);
	free(cmd);
}

void free_exec(t_exec *exec)
{
	free_env(exec->env);
    free_cmd(exec->cmd);
	close(exec->infile);
    close(exec->outfile);
    close(exec->fstdin);
    unlink(exec->infile_path);
    unlink(exec->outfile_path);
    unlink(exec->fstdin_path);
    free(exec->infile_path);
    free(exec->outfile_path);
    free(exec->fstdin_path);
    free(exec);
}
