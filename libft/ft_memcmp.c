/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:22 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/12 18:52:33 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*p1;
	const unsigned char		*p2;
	size_t					i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (n > i)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
/*
int	main()
{
	int str[20] = {1, 4, 67}; 
	int str2[20] = {6, 4, 67};
	//printf("%d\n", strcmp(str, str2));
	printf("%d\n", memcmp(str, str2, sizeof(char) * 9));
	printf("%d\n", ft_memcmp(str, str2, sizeof(char) * 9));
	return (0);
}*/
