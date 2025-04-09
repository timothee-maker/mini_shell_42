#include "../../includes/minishell.h"

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
