#include "../../includes/minishell.h"


void ft_cd(t_exec *exec)
{
    char    **args;
    char    cwd[PATH_MAX];
    t_env   *var;

    args = create_args(exec);
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        perror("cd");
        free_tab(args);
        return ;
    }
    var = exec->env;
    while(var)
    {
        if (!ft_strncmp(var->name, "PWD", ft_strlen(var->name)))
        {
            free(var->value);
            if (chdir(args[1]) == -1)
                args[1] = fetch_value("$HOME", exec);
            var->value = ft_strdup(args[1]);
            printf("value : %s\n", var->value);
        }
        if (!ft_strncmp(var->name, "OLDPWD", ft_strlen(var->name)))
        {
            free(var->value);
            var->value = ft_strdup(cwd);
        }
        var = var->next;
    }
}
