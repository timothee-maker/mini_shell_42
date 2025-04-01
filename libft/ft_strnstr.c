/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:58:34 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/13 16:58:36 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!little[j])
		return ((char *) big);
	while (big[i] && i < (unsigned int) len)
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j]
			&& (i + j) < (unsigned int) len)
		{
			j++;
			if (!little[j])
				return ((char *) big + i);
		}
		i++;
	}
	return (0);
}
