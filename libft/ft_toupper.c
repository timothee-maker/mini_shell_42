/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:46 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/13 18:23:17 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
int	main()
{
	char *s2= "Je suis ici et Toi";
	char *s1= "Je suis ici et Toi";
	int	i;
	
	while (s1[i])
	{
		toupper(s1[i]);
		printf("%c", s1[i]);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		printf("%c", ft_toupper(s2[i]));
		i++;
	}
	printf("%c", toupper('a'));

}*/
