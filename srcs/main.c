/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:53:56 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/10 16:01:38 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	analyze_line(char **split, t_list *list);
void	minishell(char	*line, t_list *list);
int		find_token(char *split, t_list *list, int index);
void	find_file(char *split, t_list *list, int index, int redir);
int		find_cmd(char *split, t_list *list, int index);
void	find_opt_arg(char *split, t_list *list, int index);
int		find_builtin(char *split, t_list *list, int index);
int		parse(char **split);
int		valid_quote(char *split);

int	main(void)
{
	char	*input;
	t_list	*list;

	while (1)
	{
		input = readline("shell_de_l'empereur : ");
		if (input)
		{
			list = initialisation();
			minishell(input, list);
			add_history(input);
			afficherliste(list);
			destruction(list);
		}
		else
			exit(1);
	}
}

void	minishell(char	*line, t_list *list)
{
	char	**split;
	int		nb_pipe;

	line = clean_line(line);
	split = ft_split(line, ' ');
	free(line);
	if (!parse(split))
	{
		free_split(split);
		printf("erreur de parsing\n");
		return;
	}
	analyze_line(split, list);
	free_split(split);
}

int		parse(char **split)
{
	int	i;
	int	len_split;
	
	len_split = len_tab(split) - 1;
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '|') && (i == 0 || i == len_split))
			return(0);
		else if (!valid_quote(split[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_quote(char *split)
{
	char 	tmp;

	if (strchr(QUOTES, split[0]))
		tmp = split[0];
	else
		return (1);
	if (split[ft_strlen(split) - 1] == tmp)
		return (1);
	return (0);
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
				if (!find_cmd(split[i], current, position_element))
					find_opt_arg(split[i], current, position_element);
			}
		}
		i++;
		position_element++;
	}
}
