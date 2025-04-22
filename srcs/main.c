/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/04/18 13:59:32 by tnolent          ###   ########.fr       */
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
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		input = readline("$> ");
		// signal(SIGINT, SIG_IGN);
		if (input[0] != '\0')
		{
			signal(SIGINT, SIG_IGN);
			liste = initialisation();
			minishell(input, liste);
            // afficherliste(liste);
			exec_line(exec, liste);
			destruction(liste);
		}
		else
			continue;
	}
}
