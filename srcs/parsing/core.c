#include "minishell.h"

typedef struct s_token
{
	char	*new_str;
	int		index;
	int		position;
}			t_token;

int			find_token(char **split, t_list *current, t_token *token);

int	parsing(char *line, t_list *list, t_exec *exec)
{
	char	**split;

	split = NULL;
	add_history(line);
	if (!(line = clean_line(line)))
		error_parsing(line, list, exec, split);
	if (!(split = ft_split_minishell(line, ' ')))
		error_parsing(line, list, exec, split);
	// printf("%s\n", line);
	// int i = 0;
	// while (split[i])
	// 	printf("[%s]", split[i++]);
	free(line);
	line = NULL;
	if (!start_parse(split))
		return (free_split(split), -1);
	if (!analyze_line(split, list))
		error_parsing(line, list, exec, split);
	free_split(split);
	return (1);
}

int	analyze_line(char **split, t_list *list)
{
	t_list	*current;
	t_token	token;

	current = list;
	token.index = 0;
	token.position = 0;
	while (split[token.index])
	{
		token.new_str = remove_quotes_around(split[token.index]);
		if (ft_strchr(split[token.index], '|') && ft_strlen(token.new_str) == 1)
		{
			insertion_list(current);
			current = current->next_list;
			free(token.new_str);
			token.new_str = remove_quotes_around(split[++token.index]);
			token.position = 0;
		}
		if (!find_token(split, current, &token))
			return (free(token.new_str), 0);
		free(token.new_str);
		token.index++;
		token.position++;
	}
	return (1);
}

int	find_token(char **split, t_list *current, t_token *token)
{
	int	is_good;

	if (!(is_good = find_builtin(token->new_str, current, token->position)))
	{
		if (!(is_good = find_files_redir(split[token->index], current,
					token->position, token->new_str)))
		{
			is_good = find_cmd(split[token->index], current, token->position,
					token->new_str);
		}
	}
	if (is_good == -1)
		return (0);
	return (1);
}
