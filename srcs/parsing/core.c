#include "minishell.h"

// typedef struct s_struct
// {
// 	char	**split;
// }	t_struct;

int		minishell(char	*line, t_list *list)
{
	char	**split;

    add_history(line);
	if (!(line = clean_line(line)))
		return (0);
	if (!(split = ft_split_minishell(line, ' ')))
		return (free(line), 0);
	// printf("%s\n", line);
	// int i = 0;
	// while (split[i])
	// 	printf("[%s]", split[i++]);
	free(line);
	if (!start_parse(split))
		return (free_split(split), 1);
	analyze_line(split, list);
	free_split(split);
	return (1);
}

int		analyze_line(char **split, t_list *list)
{
	int		i;
	int		position_element;
	char	*new_str;
	t_list	*current;

	current = list;
	i = 0;
	position_element = 0;
	while (split[i])
	{
		new_str = remove_quotes_around(split[i]);
		if (ft_strchr(split[i], '|') && ft_strlen(new_str) == 1)
		{
			insertion_list(current);
			current = current->next_list;
			free(new_str);
			new_str = remove_quotes_around(split[++i]);
			position_element = 0;
		}
		if (!find_builtin(new_str, current, position_element))
		{
			if (!find_files_redir(split[i], current, position_element, new_str))
            {
				find_cmd(split[i], current, position_element, new_str);
            }
		}
		free(new_str);
		i++;
		position_element++;
	}
	return (1);
}
