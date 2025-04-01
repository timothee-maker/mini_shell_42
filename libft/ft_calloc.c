/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:18:02 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/14 13:18:05 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int				i;
	unsigned char	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (0);
	else
	{
		i = 0;
		while ((unsigned long) i < size * nmemb)
		{
			ptr[i] = 0;
			i++;
		}
	}
	return (ptr);
}
