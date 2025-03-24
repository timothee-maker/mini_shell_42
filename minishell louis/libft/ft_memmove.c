/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:44:53 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/12 13:44:57 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*psrc;
	char	*pdst;

	if (!dst && !src)
		return (0);
	psrc = (char *) src;
	pdst = (char *) dst;
	if (pdst > psrc)
	{
		while (len-- > 0)
			pdst[len] = psrc[len];
	}
	else
		ft_memcpy(pdst, psrc, len);
	return (dst);
}
