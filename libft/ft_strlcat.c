/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:29:24 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/14 13:38:20 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	k;

	len_dest = 0;
	len_src = ft_strlen(src);
	while (dest[len_dest] && len_dest < size)
		len_dest++;
	if (len_dest == size)
		return (size + len_src);
	k = 0;
	while (src[k] && (len_dest + k) < (size - 1))
	{
		dest[len_dest + k] = src[k];
		k++;
	}
	dest[len_dest + k] = '\0';
	return (len_dest + len_src);
}

// int	main()
// {
// 	char	*s1 = "Je suis dans la joie";
// 	char	*s2 = "Je suis ici";
// 	printf("%zu\n", ft_strlcat(s1, s2, 25));
// 	// printf("%lu\n", strlcat(s1, s2, 20));
// 	// printf("%lu\n", strlcat(s1, s2, 0));
// 	printf("%d\n", ft_strlen(s1));
// 	printf("%d\n", ft_strlen(s2));
// 	printf("%s", s1);
// 	return (0);
// }