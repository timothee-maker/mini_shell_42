#include "minishell.h"

int	handle_token(t_list *current, t_token *token);

int	parsing(char *line, t_list *list, t_exec *exec)
{
	l_split	*split;

	split = NULL;
	add_history(line);
	if (!(line = clean_line(line)))
		error_parsing(line, list, exec, split);
	split = ft_split_list_minishell(line, ' ');
	if (!split)
		error_parsing(line, list, exec, split);
	// while (split){printf("[%s][env = %d]", split->str, split->env_context);split = split->next;}
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
	token.redir = 0;
	while (current_split)
	{
		token.split = current_split;
		if (ft_strchr(current_split->str, '|') && ft_strlen(token.split->str) == 1)
		{
			insertion_list(current);
			current = current->next_list;
			current_split = current_split->next;
			token.position = 0;
			token.redir = 0;
			continue ;
		}
		if (!handle_token(current, &token))
			return (0);
		token.position++;
		current_split = current_split->next;
	}
	return (1);
}


int	handle_token(t_list *current, t_token *token)
{
	int	is_good;

	if (!(is_good = find_builtin(current, token)))
	{
		if (!(is_good = find_files_redir(current, token)))
		{
			is_good = find_cmd(current, token);
		}
	}
	if (is_good == -1)
		return (0);
	return (1);
}
