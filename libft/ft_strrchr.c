/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:31 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/13 10:05:42 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	j = ft_strlen(s);
	i = 0;
	while (j > i)
	{
		if (s[j] == (char)c)
			return ((char *)&s[j]);
		j--;
	}
	if (s[j] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main()
{
	char *str = "Je suis l;a coucouc coucouc pourquoi ?";
	printf("%s\n", ft_strrchr(str, 'c'));
	printf("%s\n", strrchr(str, 'c'));
	return (0);
}
*/