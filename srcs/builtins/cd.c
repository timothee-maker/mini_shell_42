#include "../../includes/minishell.h"

void ft_cd(t_exec *exec)
{
    char **args;
    char cwd[PATH_MAX];
    t_env *var;

    args = create_args(exec);
    if (chdir(args[1]) == -1 || getcwd(cwd, PATH_MAX) == -1)
    {
        perror("cd");
        free_tab(args);
        return ;
    }
    var = exec->env;
    while (ft_strncmp(var->name, "PWD", ft_strlen(var->name)))
        var = var->next;
    free(var->value);
    var->value = ft_strdup(args[1]);
    var = exec->env;
    while (ft_strncmp(var->name, "OLDPWD", ft_strlen(var->name)))
        var = var->next;
    free(var->value);
    var->value = ft_strdup(cwd);
}
