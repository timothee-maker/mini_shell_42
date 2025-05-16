#include "minishell.h"

int			find_token(l_split *split, t_list *current, t_token *token);

int	parsing(char *line, t_list *list, t_exec *exec)
{
	l_split		*split;

	split = NULL;
	add_history(line);
	if (!(line = clean_line(line)))
		error_parsing(line, list, exec, split);
	split = ft_split_list_minishell(line, ' ');
	if (!split)
		error_parsing(line, list, exec, split);
	// while (split){printf("[%s]", split->str);split = split->next;}
	free(line);
	line = NULL;
	if (!start_parse(split))
		return (free_split(split), -1);
	if (!analyze_line(split, list))
		error_parsing(line, list, exec, split);
	free_split(split);
	return (1);
}

int	analyze_line(l_split *split, t_list *list)
{
	t_list	*current;
	t_token	token;
	l_split	*current_split;

	current_split = split;
	current = list;
	token.position = 0;
	while (current_split)
	{
		token.new_str = remove_quotes_around(current_split->str);
		token.split = current_split->str;
		if (ft_strchr(current_split->str, '|') && ft_strlen(token.new_str) == 1)
		{
			insertion_list(current);
			current = current->next_list;
			free(token.new_str);
			token.new_str = remove_quotes_around(current_split->str);
			current_split = current_split->next;
			token.position = 0;
			continue;
		}
		if (!find_token(current_split, current, &token))
			return (free(token.new_str), 0);
		free(token.new_str);
		token.position++;
		current_split = current_split->next;
	}
	return (1);
}

int	find_token(l_split *split, t_list *current, t_token *token)
{
	int	is_good;

	if (!(is_good = find_builtin(current, token)))
	{
		if (!(is_good = find_files_redir(current, split->str, 
			token)))
		{
			is_good = find_cmd(current, split->str, token);
		}
	}
	if (is_good == -1)
		return (0);
	return (1);
}
