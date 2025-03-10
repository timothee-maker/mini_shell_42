/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:53:56 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/07 16:30:55 by tnolent          ###   ########.fr       */
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

int	main(void)
{
	char	*input;
	t_list	*list;

	list = initialisation();
	while (1)
	{
		input = readline("shell_de_l'empereur : ");
		if (input)
		{
			minishell(input, list);
			add_history(input);
			afficherliste(list);
			destruction(list);
		}
		else
			exit(1);
		free(input);
	}
}

void	minishell(char	*line, t_list *list)
{
	char	**split;
	int		nb_pipe;

	line = clean_line(line);
	printf("%s\n", line);
	split = ft_split(line, ' ');
	free(line);
	analyze_line(split, list);
	free_split(split);
}

void	analyze_line(char **split, t_list *list)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (!find_builtin(split[i], list, i))
		{
			if (!find_token(split[i], list, i))
			{
				if (!find_cmd(split[i], list, i))
					find_opt_arg(split[i], list, i);
			}
		}
		i++;
	}
}
