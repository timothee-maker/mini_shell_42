/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:54:09 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/14 10:54:12 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	len;

	len = ft_strlen(src);
	if (siz > 0)
	{
		siz--;
		while (*src && siz)
		{
			*dst++ = *src++;
			siz--;
		}
		*dst = '\0';
	}
	return (len);
}
