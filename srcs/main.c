/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/05 17:39:30 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	 *input;
	t_list *liste;
	t_exec *exec;

	(void)argc;
	(void)argv;
	exec = init_exec(envp);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		input = readline("$> ");
		if (input == NULL)
            break;
		if (input[0] != '\0')
		{
			liste = initialisation();
			if (minishell(input, liste))
			{
				// afficherliste(liste);
				exec_line(exec, liste);
			}
			destruction(liste);
		}
		else
			continue ;
	}
}
