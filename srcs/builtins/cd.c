#include "../../includes/minishell.h"

void ft_cd(t_exec *exec)
{
    char    **args;
    char    cwd[PATH_MAX];
    t_env   *var;

    args = create_args(exec);
    if (chdir(args[1]) == -1 || getcwd(cwd, PATH_MAX) == NULL)
    {
        perror("cd");
        free_tab(args);
        return ;
    }
    printf("test");
    var = exec->env;
    while(var)
    {
        printf("boucle");
        if (!ft_strncmp(var->name, "PWD", ft_strlen(var->name)))
        {
            printf("PWD trouve\n");
            free(var->value);
            var->value = ft_strdup(args[1]);
        }
        if (!ft_strncmp(var->name, "OLDPWD", ft_strlen(var->name)))
        {
            printf("OLDPWD trouve\n");
            free(var->value);
            var->value = ft_strdup(cwd);
        }
        var = var->next;
    }
}
