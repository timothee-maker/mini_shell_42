#include "../minishell.h"

void	minishell(char	*line, t_list *list)
{
	char	**split;

    add_history(line);
	line = clean_line(line);
	split = ft_split(line, ' ');
	free(line);
	if (start_parse(split))
		analyze_line(split, list);
	free_split(split);
}

void	analyze_line(char **split, t_list *list)
{
	int		i;
	int		position_element;
	t_list	*current;

	current = list;
	i = 0;
	position_element = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '|'))
		{
			insertion_list(current);
			current = current->next_list;
			i++;
			position_element = 0;
		}
		if (!find_builtin(split[i], current, position_element))
		{
			if (!find_token(split[i], current, position_element))
            {
				find_cmd(split[i], current, position_element);
            }
		}
		i++;
		position_element++;
	}
}
