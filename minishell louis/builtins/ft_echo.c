/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:35:42 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/14 13:35:44 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args)
{
    int newline;

    newline = 1;
	while (*args[0] == '-')
    {
        if (!ft_strncmp(*args, "-n", ft_strlen(*args)))
            newline = 0;
        args++;
    }
    printf("%s", *args);
    if (newline)
        printf("\n");
	return (0);
}
