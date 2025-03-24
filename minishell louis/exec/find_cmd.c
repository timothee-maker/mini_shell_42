#include "../minishell.h"

int is_builtin(t_list *list)
{
    t_element *elem;

    elem = list->first;
    while (elem)
    {
        if (!ft_strncmp(elem->token, "BUILTIN", ft_strlen(elem->token)))
            return (1);
        elem = elem->next;
    }
    return (0);
}

char *get_path(char *cmd, t_env **env)
{
    char **all_path;
    char *tmp_path;
    char *exec;
    char *path_value;
    int i;

    path_value = fetch_value("PATH", env);
    all_path = ft_split(path_value, ':');
    i = 0;
    while (all_path[i])
    {
        tmp_path = ft_strjoin(all_path[i], "/");
        exec = ft_strjoin(tmp_path, cmd);
        free(tmp_path);
        if (access(exec, F_OK | X_OK) == 0)
        {
            ft_free_tab(all_path);
            return (exec);
        }
        free(exec);
        i++;
    }
    ft_free_tab(all_path);
    return (NULL);
}

