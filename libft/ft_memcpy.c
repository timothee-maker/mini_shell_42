/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:25 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/20 10:18:22 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printall(char *str);

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}
// int	main()
// {
// 	char str[20] = {'l','a',' ','\0', 'p', 'l', 'a', 'g', 'e'};
// 	char tab[100];
// 	char tab2[100];

// 	//printf("%s\n", );
// 	ft_memcpy("", "", 0);
// 	memcpy("", "", 0);
// 	// printall(tab);
// 	// printall(tab2);
// 	return (0);
// }

// void	printall(char *str)
// {
// 	int	i = 0;
// 	while (i < 9)
// 	{
// 		printf("%c", str[i]);
// 		i++;
// 	}
// 	printf("\n");

// }
