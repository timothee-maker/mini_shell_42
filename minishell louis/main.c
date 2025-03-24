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

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
    char	*input;
    t_data  *data;

    (void) argc;
    (void) argv;
	while (1)
	{
        data = init_data(envp);
		input = readline("shell_de_l'empereur : ");
        if (input)
        {
		    minishell(input, data->list);
		    exec_list(data);
		    //destruction(data->list);
        }
        else
            exit(1);
	}
}
