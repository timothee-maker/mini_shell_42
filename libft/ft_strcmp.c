/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:27:08 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:31:58 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
int	main()
{
	char	s1[] = "Je suis la plus belle caroote de la foret Okay";
	char	s2[] = "Je suis Okay";
	int	result;
	int	ptr;
	result = strcmp(s1, s2);
	ptr = ft_strcmp(s1, s2);	
	printf("%d\n", result);
	printf("%d\n", ptr);
}*/
