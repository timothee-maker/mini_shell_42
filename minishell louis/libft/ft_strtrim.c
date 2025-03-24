/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:03:12 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/18 11:03:14 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isset(char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		end;
	int		len;
	int		i;

	end = 0;
	while (ft_isset(*s1, set))
		s1++;
	if (!*s1)
		return (ft_calloc(1, sizeof(char)));
	while (ft_isset(s1[ft_strlen(s1) - (1 + end)], set))
		end++;
	len = ft_strlen(s1) - end;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = *(s1 + i);
		i++;
	}
	res[i] = '\0';
	return (res);
}
