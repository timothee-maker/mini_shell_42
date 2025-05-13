/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/12 16:01:34 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_exec *exec);

int main(int argc, char **argv, char **envp)
{
	t_exec *exec;

	(void)argc;
	(void)argv;
	exec = init_exec(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	minishell(exec);
}

void	minishell(t_exec *exec)
{
	char	*input;
	t_list	*liste;

	while (1)
	{
		input = readline("$> ");
		if (input == NULL)
            break;
		if (input[0] != '\0')
		{
			liste = initialisation();
			if (!parsing(input, liste))
				break;
			//afficherliste(liste);
			exec_line(exec, liste);
			destruction(liste);
		}
	}
}
