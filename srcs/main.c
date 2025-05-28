/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/27 13:11:29 by tnolent          ###   ########.fr       */
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
		input = readline("$> ");
        if (g_signal_pid == 130)
        {
            exec->exit_status = 130;
            g_signal_pid = 0;
        }
		if (input == NULL)
        {
			break ;
        }
		if (input[0] != '\0')
		{
			liste = initialisation();
			exec->liste = liste;
			good = parsing(input, liste, exec);
			if (good == 1)
				exec_line(exec, liste);
			free_list(liste);
			exec->liste = NULL;
		}
	}
	global_exit(exec);
}
