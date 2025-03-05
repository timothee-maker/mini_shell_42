/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:29:35 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:31:32 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
char	ft_s(unsigned int nb, char str)
{
	int	i;
	return (str);
}


int	main()
{
	char	*str = "Je suis la"; 
	char	*ptr;
	ptr = ft_strmapi(str, &ft_s);
	printf("%s", ptr);
	return (0);
}*/
