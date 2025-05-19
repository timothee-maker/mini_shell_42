#include "minishell.h"

char *get_cmd_name(char *path)
{
	int i;
	char *res;
	char **chunks;

	chunks = ft_split(path, '/');
	res = NULL;
	i = 0;
	while (chunks[i])
	{
		if (!chunks[i + 1])
			res = ft_strdup(chunks[i]);
		i++;
	}
	free_tab(chunks);
	return (res);
}

char *find_path(char *name, t_exec *exec)
{
    char *path;
    char *temp;
    char **path_tab;
    int i;

    path = fetch_value("$PATH", exec);
    if (path == NULL)
        return (NULL);
    path_tab = ft_split(path, ':');
    i = 0;
    while (path_tab[i++])
    {
        temp = ft_strjoin(path_tab[i], "/");
        temp = ft_custom_join(temp, name);
        if (access(temp, X_OK) == 0)
        {
            free(path);
            free_tab(path_tab);
            return (temp);
        }
        free(temp);
    }
    free_tab(path_tab);
    free(path);
    return (NULL);
}
