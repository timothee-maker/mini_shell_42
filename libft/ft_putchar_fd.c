/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:36 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:32:20 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main()
{
	FILE* fichier = NULL;

	fichier = fopen("test.txt", "w");

	if (fichier != NULL)
	{
		ft_putchar_fd('A', 4); // Écriture du caractère A
		fclose(fichier);
	}

	return 0;
}*/
