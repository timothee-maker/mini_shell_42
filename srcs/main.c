/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:53:56 by tnolent           #+#    #+#             */
/*   Updated: 2025/02/25 13:22:57 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char	*input;

	while (1)
	{
		input = readline("shell_de_l'empereur >");
		if (input)
			add_history(input);
		if (input == NULL)
			break;
	}
}

void	minishell(char	*line)
{
	
}
