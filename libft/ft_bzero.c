/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:25:02 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:25:33 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(tab + i) = 0;
		i++;
	}
}

/*
int	main()
{
	char *tab = "Je suis la";
	int	src[10] = {2, 4};
	int	src2[10] = {2, 4};
	bzero(src, sizeof(int) * 10);
	//ft_bzero(src, sizeof(int) * 10);
	int	i;
	for (i = 0; i < 10; i++)
		printf("%d", src[i]);
	return (0);
}
*/
