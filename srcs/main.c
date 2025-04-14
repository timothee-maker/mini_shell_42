/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/04/14 10:20:10 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_list *liste;
	t_exec *exec;

	(void)argc;
	(void)argv;
	exec = init_exec(envp);
	while (1)
	{
		input = readline("$> ");
		if (input[0] != '\0')
		{
			liste = initialisation();
			minishell(input, liste);
            //afficherliste(liste);
			exec_line(exec, liste);
			destruction(liste);
		}
		else
			continue;
	}
}
