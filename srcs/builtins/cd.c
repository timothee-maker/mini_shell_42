#include "../../includes/minishell.h"

int update_currpwd(t_env *var, char *path)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        ft_putendl_fd("cd: Cannot access current directory", 2);
        return (1);
    }
    while (var)
    {
        if (!ft_strncmp(var->name, "PWD", ft_strlen(var->name) + 6))
        {
            free(var->value);
            var->value = ft_strdup(path);
            return (0);
        }
        var = var->next;
    }
    return (1);
}

int update_oldpwd(t_env *var)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        ft_putendl_fd("cd: Cannot access current directory", 2);
        return (1);
    }
    while (var)
    {
        if (!ft_strncmp(var->name, "OLDPWD", ft_strlen(var->name) + 6))
        {
            free(var->value);
            var->value = ft_strdup(cwd);
            return (0);
        }
        var = var->next;
    }
    return (1);
}

int ft_cd(t_exec *exec)
{
    int res;
    t_env *var;
    char **args;

    var = exec->env;
    args = create_args(exec);
    if (!args[1])
        return (home_case(exec, var));
    else if (!ft_strncmp(args[1], "-", ft_strlen(args[1]) + 1))
        return (reverse_case(exec, var));
    else
        res = base_case(var, args);
    if (res < 0)
        res *= -1;
    free_tab(args);
    return res;
}
