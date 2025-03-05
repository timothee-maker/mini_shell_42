/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:24 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/06 14:31:28 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && n > i)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
/*
int	main()
{
	return (0);
}*/
