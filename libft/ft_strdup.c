/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:28:02 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:31:52 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main()
{
	char str[] = "Je suis la";	
	char *ptr;
	ptr = ft_strdup(str);
	char *ptr2 = strdup(str);
	printf("%s", ptr);
	free(ptr);
	return (0);
}*/
