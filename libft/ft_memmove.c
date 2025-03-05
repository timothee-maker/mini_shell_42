/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:30 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/20 10:17:16 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			i--;
			*(char *)(dst + i) = *(char *)(src + i);
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	return ((void *)dst);
}
/*
void	printall(char *str);
int	main(void)
{
	char	str[20] = {'l','a',' ','\0', 'p', 'l', 'a', 'g', 'e'};
	char	str2[20] = {'l','a',' ','\0', 'p', 'l', 'a', 'g', 'e'};
	char	tab[100];
	char	tab2[100];

	//printf("%s\n", );
	//ft_memmove(tab, str, sizeof(char) * 9);
	//ft_memcpy(tab, str, sizeof(char) * 7);
	ft_memmove(tab, str2, sizeof(char) * 5);
	memmove(tab2, str, sizeof(char) * 5);
	printall(tab);
	printall(tab2);
	return (0);
}

void	printall(char *str)
{
	int	i = 0;
	while (i < 9)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}*/
