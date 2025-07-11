/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:31:20 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/19 12:31:23 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (str == NULL)
	{
		return ;
	}
	if (fd < 0)
		return ;
	i = 0;
	while (str[i])
	{
		if (write(fd, &str[i], 1) == -1)
		{
			write(STDOUT_FILENO, "write error\n", 12);
			return ;
		}
		i++;
	}
}
