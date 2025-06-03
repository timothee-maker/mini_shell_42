/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/02 16:50:37 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal_pid;
void	minishell(t_exec *exec);

int	main(int argc, char **argv, char **envp)
{
	t_exec	*exec;

	(void)argc;
	(void)argv;
	if (!isatty(0) || !isatty(1))
		return (printf("Erreur\n"), 1);
	exec = init_exec(envp);
	signals();
	g_signal_pid = 0;
	minishell(exec);
}

void	minishell(t_exec *exec)
{
	char	*input;
	t_list	*liste;
	int		good;

	good = 0;
	while (1)
	{
		if (g_signal_pid == 130)
			exec->exit_status = 130;
		g_signal_pid = 0;
		input = readline("$> ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			liste = initialisation();
			exec->liste = liste;
			good = parsing(input, liste, exec);
			// afficherliste(liste);
			if (good == 1)
				exec_line(exec, liste);
			free_list(exec, liste);
		}
	}
	global_exit(exec, 0);
}
