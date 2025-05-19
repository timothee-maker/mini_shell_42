#include "minishell.h"

void	init_split(t_split_parse *split)
{
	split->i = 0;
	split->tmp = 0;
	split->dollar = 0;
	split->is_in_quotes = 0;
	split->env_context = 0;
	split->buffer = NULL;
	split->head = NULL;
	split->tail = NULL;
}

void	append_to_list(t_split_parse *split, const char *content)
{
	l_split	*new;

	new = malloc(sizeof(l_split));
	if (!new)
		return ;
	new->str = ft_strdup(content);
	new->next = NULL;
	new->is_in_quotes = 0;
	new->env_context = 0;

	if (split->is_in_quotes == 1)
		new->is_in_quotes = 1;
	if (split->env_context != 0)
		new->env_context = split->env_context;

	if (!split->head)
		split->head = new;
	else
		split->tail->next = new;
	split->tail = new;
}

void	flush_buffer(t_split_parse *split)
{
	if (split->buffer && split->buffer[0])
		append_to_list(split, split->buffer);
	free(split->buffer);
	split->buffer = NULL;
}
