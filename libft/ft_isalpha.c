/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:25:52 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:33:19 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	return (0);
}
/*
int	main()
{
	char *a = "Je suis la";
	int i = 0;
	while (a[i])
	{
		if (ft_isalpha(a[i]))
			printf("%c", a[i]);
		i++;
	}
	return (0);
}*/
