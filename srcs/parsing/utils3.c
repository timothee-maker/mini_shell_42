#include "minishell.h"

void	error_parsing(char *line, t_list *list, t_exec *exec, l_split *split)
{
	if (line)
		free(line);
	if (split)
		free_split(split);
	if (exec)
		free_exec(exec);
	if (list)
		free_list(list);
	printf("AYYYYYYY le malloc a pete");
	exit(0);
}

char	*chr_str(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j])
		{
			if (str[i] == to_find[j++])
				return (str);
		}
		i++;
	}
	return (NULL);
}

int		is_in_quotes(int position, char *str)
{
	int		i;
	char	tmp;

	i = 0;
	tmp = 0;
	if (!str[position])
		return (0);
	while (str[i])
	{
		if (tmp == 0 && ft_strchr(QUOTES, str[i]))
			tmp = str[i];
		else if (ft_strchr(QUOTES, str[i]) && tmp)
			tmp = 0;
		if (i == position && tmp != 0)
			return (1);
		i++;
	}
	return (0);
}

