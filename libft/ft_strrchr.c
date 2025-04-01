/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:19:15 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/13 15:19:17 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;
	char	chr;

	ptr = 0;
	i = 0;
	chr = (char) c;
	while (s[i])
	{
		if (s[i] == chr)
			ptr = ((char *)s + i);
		i++;
	}
	if (chr == '\0')
		ptr = ((char *)s + i);
	return (ptr);
}
