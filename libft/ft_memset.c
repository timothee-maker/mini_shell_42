/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:33 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:32:22 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *tab, int c, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		*(char *)(tab + i) = (char)c;
		i++;
	}
	return (tab);
}
/*
int	main()
{
	char str[10];
	int str2[] = {10, 20, 5, 64, 432};
	char src[] = "Je suis la";
	ft_memset(str, 'a', sizeof(char) * 5);
	ft_memset(str+5, 'B', sizeof(char) * 5);	
	int	i;
	for (i = 0; i < 10; i++)
		printf("%c ", str[i]);
}*/
