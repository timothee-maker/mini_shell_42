/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:43:26 by lde-guil          #+#    #+#             */
/*   Updated: 2024/11/12 10:43:27 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
	{
		return (0);
	}
	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}
