#include "../../includes/minishell.h"

void free_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void free_env(t_env **env)
{
    int i;

    i = 0;
    while(env[i] != NULL)
    {
        free(env[0]->name);
        free(env[0]->value);
        free(env[0]);
        i++;
    }
}

void free_filenode(t_filenode *fnode)
{
    t_filenode *temp;

    while(fnode != NULL)
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
    free(cmd->path);
    free_filenode(cmd->infiles);
    free_filenode(cmd->outfiles);
    free(cmd);
}

void free_exec(t_exec *exec)
{
    free_env(exec->env);
    close(exec->infile);
    close(exec->outfile);
}
