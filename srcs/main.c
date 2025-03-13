/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:53:56 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/12 15:46:07 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	analyze_line(char **split, t_list *list);
void	minishell(char	*line, t_list *list);

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
				if (!find_cmd(split[i], current, position_element))
					find_opt_arg(split[i], current, position_element);
			}
		}
		i++;
		position_element++;
	}
}
