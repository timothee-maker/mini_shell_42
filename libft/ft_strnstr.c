/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:29 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/13 10:29:14 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*src;

	src = (char *)haystack;
	i = 0;
	if (*needle == '\0')
		return (src);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return (&src[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
// int	main()
// {
// 	char	str[] = "Je suis une chaine trouvee";
// 	char	str2[] = "suis une";
// 	char	*result;
// 	char	*ptr;
// 	// result = strnstr(str, str2, 11);
// 	ptr = ft_strnstr(str, str2, 11);	
// 	// printf("%s", result);
// 	printf("%s\n", ptr);

// 	return 0;
// }