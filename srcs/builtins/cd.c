#include "../../includes/minishell.h"

static int ft_tab_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

static int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void ft_cd(t_exec *exec)
{
    char    **args;
    char    cwd[PATH_MAX];
    t_env   *var;

    args = create_args(exec);
    if (ft_tab_len(args) > 2)
    {
        ft_putendl_fd("cd: too many arguments", 2);
        free_tab(args);
        return ;
    }
    if (!is_regular_file(args[1]))
    {
        printf("cd: %s: Not a directory", args[1]);
        free_tab(args);
        return ;
    }
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
        }
        if (!ft_strncmp(var->name, "OLDPWD", ft_strlen(var->name)))
        {
            free(var->value);
            var->value = ft_strdup(cwd);
        }
        var = var->next;
    }
}
