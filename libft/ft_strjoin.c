/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:29:20 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/12 10:45:14 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		length;
	char	*ptr;

	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	j = 0;
	if (!(s1 || s2))
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (length + 1));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = '/';
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main()
{
	char *str = "Je suis al plge";
	char *str2 = " et toi ?";
	char *ptr;
	ptr = ft_strjoin(str, str2);
	printf("%s\n", ptr);
	//free(ptr);
	return (0);
}*/
