/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:50:47 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/12 11:50:49 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	pdst = (unsigned char *) dest;
	psrc = (unsigned char *) src;
	while (n)
	{
		*(pdst++) = *(psrc++);
		n--;
	}
	return (dest);
}
