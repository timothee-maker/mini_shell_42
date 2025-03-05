/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:29:27 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/13 18:08:28 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (j);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
// /*
// int	main(void)
// {
// 	char	s1[] = "Le caca est cuitvso;kdnh;asod";
// 	char	s2[] = "Le caca est cuithypothequement";
// 	char	str1[20];
// 	char	str2[20];

// 	printf("%zu\n", ft_strlcpy(str1, s1, 7));
// 	printf("%zu\n", strlcpy(str2, s2, 7));
// 	// size_t i = strlcpy(str2, s2, 7);
// 	printf("%s\n", str1);
// 	// printf("%s\n", str2);
// 	return (0);
// }