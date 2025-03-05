/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:29:56 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/13 10:41:32 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t nb)
{
	unsigned int	i;

	i = 0;
	if (nb == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < (nb - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main()
{
	char	s1[] = "Je suis la plus belle caroote de la foret Okay";
	char	s2[] = "Je suis Okay";
	int	result;
	int	ptr;
	result = strncmp(s1, s2, 21);
	ptr = ft_strncmp(s1, s2, 21);
	printf("%d\n", result);
	printf("%d\n", ptr);
}*/
