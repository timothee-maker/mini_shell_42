/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/28 11:38:10 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal_pid;
void	minishell(t_exec *exec);

static int	valid_input(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '\0')
		return (0);
	while (input[i])
	{
		if (input[i++] != ' ')
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	*exec;

	(void)argc;
	(void)argv;
	// if (!isatty(0) || !isatty(1))
	// 	return (printf("Erreur\n"), 1);
	exec = init_exec(envp);
	ft_malloc(0, 0, exec);
	exit_malloc_failure(exec);
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
			exec->exit_status = 130;
		g_signal_pid = 0;
		if (input == NULL)
			break ;
		if (valid_input(input))
		{
			liste = initialisation();
			exec->liste = liste;
			good = parsing(input, liste, exec);
			if (good == 1)
				exec_line(exec, liste);
			free_list(exec, liste);
		}
	}
	printf("exit\n");
	global_exit(exec, 0);
}
