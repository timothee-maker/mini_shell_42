/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:25:47 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/14 13:25:49 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
    char	*input;
    t_list  *liste;
    t_exec  *exec;

    (void) argc;
    (void) argv;
    liste = initialisation();
    exec = init_exec(envp);
	while (1)
	{
		input = readline("$>");
        if (input)
        {
		    minishell(input, liste);
            //afficherliste(liste);
            exec_line(exec, liste);
		    destruction(liste);
        }
        else
            exit(1);
	}
}
